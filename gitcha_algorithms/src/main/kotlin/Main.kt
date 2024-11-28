package com.yamadalab.gitcha

fun callDrawFunction() {
    val random: Random = Random();

    val items: Array<Pair<String, Pair<Double, Int>>> = arrayOf(
        Pair("Item1", Pair(5.1, 0)),
        Pair("Item2", Pair(4.1, 1)),
        Pair("Item3", Pair(3.1, 2)),
        Pair("Item4", Pair(2.1, 3)),
        Pair("Item5", Pair(1.1, 4)),
        Pair("Item6", Pair(0.1, 5)),
        Pair("Item7", Pair(9.1, 6)),
        Pair("Item8", Pair(8.1, 7)),
        Pair("Item9", Pair(7.1, 8)),
        Pair("Item10", Pair(6.1, 9)),
        Pair("Item11", Pair(5.1, 10)),
        Pair("Item12", Pair(4.1, 11)),
    );

    val drawResultId: String = random.draw(items);

    if (drawResultId == "") {
        println("DrawResultID is empty");
    } else if (drawResultId == "9999") {
        println("ItemList is Empty");
    } else if (drawResultId == "5000") {
        println("API Error");
    } else {
        println("DrawResultID : $drawResultId");
    }
}

fun main() {
    callDrawFunction();
}