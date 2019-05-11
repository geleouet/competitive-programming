package org.meritis.battledev.exo2

import java.io._

class RunExercise {

    def compute(list: List[Int], weight: Int, count: Int): Int = list match {
        case Nil if weight >= 0 => count + 1
        case Nil                => count
        case head :: tail if weight+head > 100  => compute(tail, head, count + 1)
        case head :: tail                       => compute(tail, weight+head, count)
    }

    def input = io.Source.stdin.getLines.toList
    def output(result: Int) = System.out.println(result.toString)

    def contestResponse() {
        val in = input
        
        val N = in.head.toInt
        val weights = in.tail.map(line => line.toInt)

        val result = compute(weights, 0, 0)
        
        output(result)
    }

}
