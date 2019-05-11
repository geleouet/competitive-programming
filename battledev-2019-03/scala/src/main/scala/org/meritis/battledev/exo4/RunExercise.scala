package org.meritis.battledev.exo4

import java.io._
 
class RunExercise {
 
    def makeCombinations(word: String, lettersRemoved: Int, indexes: List[Seq[Int]]): Set[String] = {
        if (lettersRemoved == 0) Set(word)
        else indexes.map(list => list.map(i => word(i)).mkString).toSet
    }
 
    def intersectAll(combinations: List[Set[String]]): Set[String] = {
        combinations.foldLeft(combinations.head) {
            (acc, set) => acc.intersect(set)
        }
    }
 
    def testNbLettersRemoved(i: Int, words: List[String]): Option[String] = {
        val indexes = (0 until 10).combinations(10 - i).toList

        val combinations = words.map(word => makeCombinations(word, i, indexes))
        val intersection = intersectAll(combinations)

        if (!intersection.isEmpty) Some(intersection.head) else None
    }
 
    def input = io.Source.stdin.getLines.toList
    def output(result: String) = System.out.println(result)

    def contestResponse() {
        val in = input
        
        val wordCount = in.head.toInt
        val words = in.tail

        val result = (0 until 10).map(testNbLettersRemoved(_, words)).find(x => !x.isEmpty)

        val resultAsText = if (!result.isEmpty) result.get.get else "KO"
        output(resultAsText)
    }
 
}
