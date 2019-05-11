package org.meritis.battledev.exo6

import java.io._
import scala.collection.mutable.HashSet


trait RollingHash {
    def sentence: Vector[Char]
    def size: Int
    def firstHash(start: Int): Int
    def nextHash(previousHash: Int, outChar: Char, inChar: Char): Int

    def hashList: List[Int] = {
        val first = firstHash(0)
        val list = (1 until (sentence.length - size + 1)).foldLeft(List(first)) {
            (acc, i) => nextHash(acc.head, sentence(i-1), sentence(i+size-1)) :: acc
        }
        list.reverse
    }
}


class SimpleRollingHash(val sentence: Vector[Char], val size: Int) extends RollingHash {
    def firstHash(start: Int): Int = {
        sentence.slice(start, start + size).map(c => c.toInt).sum
    }

    def nextHash(previousHash: Int, outChar: Char, inChar: Char): Int = {
        previousHash + inChar.toInt - outChar.toInt
    }
}


object Transcoder {
    val rand = new scala.util.Random
    val transcode = (0 until Char.MaxValue.toInt - 1).map(i => rand.nextInt).toVector
}

class RabinKarpHash(val sentence: Vector[Char], val size: Int) extends RollingHash {
    val B: Int = 31
    val BtoN: Int = List.fill(size)(B).foldLeft(1)((acc, x) => acc * x)

    def firstHash(start: Int): Int = {
        sentence.slice(start, start + size).foldLeft(0) {
            (acc, char) => acc * B + Transcoder.transcode(char.toInt)
        }
    }

    def nextHash(previousHash: Int, outChar: Char, inChar: Char): Int = {
        B * previousHash + Transcoder.transcode(inChar.toInt) - BtoN * Transcoder.transcode(outChar.toInt)
    }
}


class RunExercise {

    // Works for small patterns (until 1000)
    // Enough for test cases until 5
    def smallPatternCheck(sentence1: String, sentence2: String, n: Int): Boolean = {
        val set1 = HashSet[String]()
        val set2 = HashSet[String]()

        for (i <- 0 until (sentence1.length - n + 1)) {
            set1 += sentence1.slice(i, i + n)
            set2 += sentence2.slice(i, i + n)
        }

        !set1.intersect(set2).isEmpty
    }

    // Works for large patterns using rolling hash
    def largePatternCheck(sentence1: String, sentence2: String, n: Int): Boolean = {
        val list1 = new RabinKarpHash(sentence1.toVector, n).hashList.toVector
        val list2 = new RabinKarpHash(sentence2.toVector, n).hashList.toVector

        val intersection = list1.toSet.intersect(list2.toSet)

        if (intersection.isEmpty) {
            false
        } else {
            val size = sentence1.length - n + 1
            val range = 0 until n

            val compares = for (hashCode <- intersection;
                                i <- 0 until size if list1(i) == hashCode;
                                j <- 0 until size if list2(j) == hashCode)
                            yield !range.exists(k => sentence1.charAt(i+k) != sentence2.charAt(j+k))

            compares.exists(x => x == true)
        }
    }
        
    def dichotomy(nMin: Int, nMax: Int, sentence1: String, sentence2: String, test: (String, String, Int) => Boolean): Int = {
        if (nMax - nMin <= 10) {
            System.err.println("check all values within [" + nMin + "," + nMax + "]")

            val results = for (n <- nMin to nMax if test(sentence1, sentence2, n)) yield (n)
            results.max
            
        } else {
            val n = (nMax + nMin) / 2
            System.err.println("check once for n=" + n)

            if (test(sentence1, sentence2, n)) dichotomy(n, nMax, sentence1, sentence2, test)
            else dichotomy(nMin, n, sentence1, sentence2, test)
        }
    }
    
    def input = io.Source.stdin.getLines.toList
    def output(result: Int) = System.out.println(result)

    def contestResponse() {
        val in = input
        
        val N = in.head.toInt
        System.err.println("\nN=" + N)
        
        val sentence1 = in(1)
        val sentence2 = in(2)
        
        val result = dichotomy(1, N, sentence1, sentence2, largePatternCheck)
        output(result)
    }
    
}
