package org.meritis.battledev.exo3

import scala.collection.mutable.ListBuffer
import org.scalatest.FunSuite
import scala.io.Source

class RunExerciseTest extends FunSuite {

    class RunExerciseMock(grid: List[String]) extends RunExercise {
        val mockBuffer = new ListBuffer[String]()

        override def input = grid.size.toString :: grid
        override def output(result: String) = (mockBuffer += result)

        def hasResult = !mockBuffer.isEmpty
        def testResult = mockBuffer.head
    }

    def useOnlyLegalChars(result: String): Boolean = {
        result.toSet subsetOf Set('<', '>', '^', 'v', 'x')
    }

    def generatePositions(result: String): List[(Int, Int)] = {
        def dx(char: Char) = if (char == '>') 1 else if (char == '<') -1 else 0
        def dy(char: Char) = if (char == '^') -1 else if (char == 'v') 1 else 0

        val deltas = result.map(c => (dx(c), dy(c)))
        deltas.scanLeft((0, 0))((acc, elt) => (acc._1 + elt._1, acc._2 + elt._2)).toList
    }

    def useOnlyLegalMoves(grid: List[String], result: String): Boolean = {
        val height = grid.size
        val width = grid.head.length
        val positions = generatePositions(result)

        !positions.exists(m => m._1 < 0 || m._2 < 0 || m._1 >= width || m._2 >= height)
    }

    def pickUpPositions(result: String): List[(Int, Int)] = {
        val positions = generatePositions(result)
        (for (i <- 1 until positions.size if positions(i-1) == positions(i)) yield positions(i)).toList
    }

    def pickUpOnlyObjects(grid: List[String], result: String): Boolean = {
        val positions = pickUpPositions(result)
        !positions.exists(pos => grid(pos._2).charAt(pos._1) != 'o' && grid(pos._2).charAt(pos._1) != '*')
    }

    def pickUpOnlyOnce(grid: List[String], result: String): Boolean = {
        val positions = pickUpPositions(result)
        !positions.groupBy(x => x).exists(e => e._2.size > 1)
    }

    def findObjects(grid: List[String], result: String): List[Char] = {
        pickUpPositions(result).map(pos => grid(pos._2).charAt(pos._1))
    }

    def doChecks(grid: List[String], result: String, expectedObjects: List[Char]) = {
        assert(useOnlyLegalChars(result), "Algo did not use legal caracters")
        assert(useOnlyLegalMoves(grid, result), "Algo moved out of limits")
        assert(pickUpOnlyObjects(grid, result), "Algo tried to pick up an object in an empty location")
        assert(pickUpOnlyOnce(grid, result), "Algo tried to pick up twice the same object")
        assert(findObjects(grid, result) === expectedObjects, "Algo did not reach the highest score")
    }

    test("Exo 3 : Test 4x4") {
        val grid = Source.fromURL(getClass.getResource("/exo3_input1.txt")).getLines.toList
        val exo = new RunExerciseMock(grid)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else doChecks(grid, exo.testResult, List.fill(2)('o') ++ List.fill(1)('*'))
    }

    test("Exo 3 : Test 10x10") {
        val grid = Source.fromURL(getClass.getResource("/exo3_input2.txt")).getLines.toList
        val exo = new RunExerciseMock(grid)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else doChecks(grid, exo.testResult, List.fill(25)('o') ++ List.fill(26)('*'))
    }

    test("Exo 3 : Test 20x20") {
        val grid = Source.fromURL(getClass.getResource("/exo3_input3.txt")).getLines.toList
        val exo = new RunExerciseMock(grid)
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else doChecks(grid, exo.testResult, List.fill(107)('o') ++ List.fill(104)('*'))
    }

}
