package org.meritis.battledev.exo3

import java.io._

class RunExercise {

    def transform1Line(width: Int, line: String, specialCar: Char): String = {
        val leftToRight = line.map(c => if (c != specialCar) ">" else "x>").mkString
        val backToLeft =  "<" * (width-1)
        
        leftToRight.dropRight(1) + backToLeft
    }
    
    def transformAllLines(width: Int, lines: List[String], specialCar: Char): String = {
        val allLines = lines.map(line => transform1Line(width, line, specialCar))
        val backToUp = "^" * (width-1)
        
        allLines.mkString("v") + backToUp
    }

    def input = io.Source.stdin.getLines.toList
    def output(result: String) = System.out.println(result)

	def contestResponse() {
	    val in = input
	    
	    val width = in.head.toInt
	    val lines = in.tail
	    
	    val pickUpGold = transformAllLines(width, lines, 'o')
	    val pickUpMultiply = transformAllLines(width, lines, '*')
	    
	    output(pickUpGold + pickUpMultiply)
	}
	
}
