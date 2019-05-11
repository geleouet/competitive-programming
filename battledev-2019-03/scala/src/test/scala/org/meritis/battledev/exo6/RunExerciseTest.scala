package org.meritis.battledev.exo6

import scala.collection.mutable.ListBuffer
import org.scalatest.FunSuite
import scala.io.Source

class RunExerciseTest extends FunSuite {

//
//
// Exercises tests
//
//

    class RunExerciseMock(sentence1: String, sentence2: String) extends RunExercise {
        val mockBuffer = new ListBuffer[Int]()

        override def input = List(sentence1.length.toString, sentence1, sentence2)
        override def output(result: Int) = (mockBuffer += result)

        def hasResult = !mockBuffer.isEmpty
        def testResult = mockBuffer.head
    }

    test("Exo 6 : small size") {
        val exo = new RunExerciseMock("bonjour", "abonnes")
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === 3)
    }

    test("Exo 6 : medium size") {
        val exo = new RunExerciseMock("rcrccrcrcccrrccrrccc", "rcccrccrcccrcrcccrrc")
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === 11)
    }

    test("Exo 6 : large size") {
        val lines = Source.fromURL(getClass.getResource("/exo6_input.txt")).getLines.toList
        val exo = new RunExerciseMock(lines(1), lines(2))
        exo.contestResponse()
        if (!exo.hasResult) fail("no result returned")
        else assert(exo.testResult === 29400)
    }


//
//
// Rolling hash tests
//
//

    val short = "salutcommentcavadede"

    def doChecks(algo: RollingHash) = {
        val ref = for (i <- 0 until algo.sentence.length - algo.size + 1) yield algo.firstHash(i)
        val list = algo.hashList

        assert(ref === list, "The rolling hash is not consistent with the regular hash code")
    }

    test("Exo 6 : Test simple hash with short sentence and pattern size 3") {
        doChecks(new SimpleRollingHash(short.toVector, 3))
    }

    test("Exo 6 : Test simple hash with long sentence and pattern size 5") {
        doChecks(new SimpleRollingHash((short * 1000).toVector, 5))
    }

    test("Exo 6 : Test simple hash with long sentence and pattern size 1000") {
        doChecks(new SimpleRollingHash((short * 1000).toVector, 1000))
    }

    test("Exo 6 : Test Rabin Karp hash with short sentence and pattern size 3") {
        doChecks(new SimpleRollingHash(short.toVector, 3))
    }

    test("Exo 6 : Test Rabin Karp hash with long sentence and pattern size 5") {
        doChecks(new SimpleRollingHash((short * 1000).toVector, 3))
    }

    test("Exo 6 : Test Rabin Karp hash with long sentence and pattern size 25000") {
        doChecks(new SimpleRollingHash((short * 2000).toVector, 25000))
    }

}
