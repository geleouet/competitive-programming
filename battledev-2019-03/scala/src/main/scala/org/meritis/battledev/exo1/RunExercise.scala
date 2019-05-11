package org.meritis.battledev.exo1

import java.io._

class RunExercise {

    def bet(ranking: Int) = {
        if (ranking <= 100) 1000
        else if (ranking <= 10000) 100
        else 0
    }
    
    def input = io.Source.stdin.getLines.toList
    def output(result: String) = System.out.println(result)

	def contestResponse() {
	    val in = input

	    val firstRanking = in.head.toInt
	    
	    val deltas = for (line <- in.tail) yield {
		    val Array(x, y) = for(i <- line split " ") yield i.toInt
		    (x-y)
	    }
	    
		val ranking = firstRanking + deltas.sum
		val amount = bet(ranking)
		
		if (amount <= 0) output("KO") else output(amount.toString)
	}
	
}
