package org.meritis.battledev.exo5

import java.io._

class RunExercise {

	def compute(amount: Int, elt: Char) = if (elt == '*') amount * 2 else amount + 1

	// Use brute-force way to solve the problem
	// Works only for tests 1 & 2
	def brutForce(left: List[Char], right: List[Char]): (Int, List[Char]) = {
		def rec(left: List[Char], right: List[Char], amount: Int, solution: List[Char]): (Int, List[Char]) =
			(left, right) match {
				case (Nil, Nil) => (amount, solution)

				case (leftElt :: leftTail, Nil)   => rec(leftTail, Nil, compute(amount, leftElt), leftElt :: solution)
				case (Nil, rightElt :: rightTail) => rec(Nil, rightTail, compute(amount, rightElt), rightElt :: solution)

				case (leftElt :: leftTail, rightElt :: rightTail) => {
					val firstOption = rec(leftTail, right, compute(amount, leftElt), leftElt :: solution)
					val secondOption = rec(left, rightTail, compute(amount, rightElt), rightElt :: solution)

					if (firstOption._1 >= secondOption._1) firstOption else secondOption
				}
		}

		val solution = rec(left, right, 0, Nil)
		(solution._1, solution._2.reverse)
	}

	// Reverse the problem and divide it into smaller problems to make it easier to solve
	// Works only for tests 1 & 2
	def divideToWin(left: List[Char], right: List[Char]): (Int, List[Char]) = (left, right) match {
		case (_, Nil) => {
			val amount = left.foldLeft(0)((acc, elt) => compute(acc, elt))
			(amount, left)
		}

		case (Nil, _) => {
			val amount = right.foldLeft(0)((acc, elt) => compute(acc, elt))
			(amount, right)
		}

		case (_, _) => {
			val leftElt = left.last
			val option1 = divideToWin(left.slice(0, left.size - 1), right)
			val amount1 = compute(option1._1, leftElt)

			val rightElt = right.last
			val option2 = divideToWin(left, right.slice(0, right.size - 1))
			val amount2 = compute(option2._1, rightElt)

			if (amount1 >= amount2) (amount1, option1._2 ++ List(leftElt))
			else (amount2, option2._2 ++ List(rightElt))
		}
	}

	// Use memoisation to build a function containing a cache to compute only once each value
	def memoisationBuilder(): (List[Char], List[Char]) => (Int, List[Char]) = {
		val cache = scala.collection.mutable.HashMap.empty[(List[Char], List[Char]), (Int, List[Char])]

		def rec(left: List[Char], right: List[Char]): (Int, List[Char]) = {
			if (cache.contains((left, right))) {
				cache((left, right))
			} else {
				val solution = (left, right) match {
					case (_, Nil) => {
						val amount = left.foldLeft(0)((acc, elt) => compute(acc, elt))
						(amount, left)
					}

					case (Nil, _) => {
						val amount = right.foldLeft(0)((acc, elt) => compute(acc, elt))
						(amount, right)
					}

					case (_, _) => {
						val leftElt = left.last
						val option1 = rec(left.slice(0, left.size - 1), right)
						val amount1 = compute(option1._1, leftElt)

						val rightElt = right.last
						val option2 = rec(left, right.slice(0, right.size - 1))
						val amount2 = compute(option2._1, rightElt)

						if (amount1 >= amount2) (amount1, option1._2 ++ List(leftElt))
						else (amount2, option2._2 ++ List(rightElt))
					}
				}
				cache.put((left, right), solution)
				solution
			}
		}

		rec
	}

    def input = io.Source.stdin.getLines.toList
    def output(result: String) = System.out.println(result)

    def solver: (List[Char], List[Char]) => (Int, List[Char]) = memoisationBuilder()

    def contestResponse() {
        val in = input
        
        val N = in.head.toInt
        System.err.println("\nN=" + N)
        
        val corridor = in(1)
        System.err.println("corridor=" + corridor)
        val sides = corridor.toList.splitAt(corridor.indexOf('X'))
        val left = sides._1.reverse
        val right = sides._2.drop(1)
        System.err.println("left=" + left)
        System.err.println("right=" + right)
        
        val result = solver(left, right)
        System.err.println("last amount=" + result._1)
        System.err.println("solution=" + result._2.mkString)
        output(result._2.mkString)
    }
    
}
