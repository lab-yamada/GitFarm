package com.yamadalab.gitfarm

import com.yamadalab.gitfarm.application.Random
import com.yamadalab.gitfarm.domain.Item

fun callDrawFunction() {
    val random: Random = Random();

    val items: Array<Item> = arrayOf(
        Item("Item1", 0.1, 0),
        Item("Item2", 1.1, 1),
        Item("Item3", 2.1, 2),
        Item("Item4", 3.1, 3),
        Item("Item5", 4.1, 4),
        Item("Item6", 5.1, 5),
        Item("Item7", 6.1, 6),
        Item("Item8", 7.1, 7),
        Item("Item9", 8.1, 8),
        Item("Item10", 9.1, 9),
        Item("Item11", 10.1, 10),
        Item("Item12", 11.1, 11),
        Item("Item13", 12.1, 12),
        Item("Item14", 13.1, 13),
        Item("Item15", 14.1, 14),
        Item("Item16", 15.1, 15),
        Item("Item17", 16.1, 16)
    );

    val drawResultId: String = random.draw(items);

    if (drawResultId == "") {
        println("DrawResultID is empty");
    } else if (drawResultId == "9999") {
        println("ItemList is Empty");
    } else if (drawResultId == "5000") {
        println("API Error");
    } else {
        println("DrawResultID : [$drawResultId]");
    }
}

fun main() {
    callDrawFunction();
}