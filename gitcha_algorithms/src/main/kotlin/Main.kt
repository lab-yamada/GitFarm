package com.yamadalab.gitcha

fun main() {
    val random: Random = Random();

    val weights: LongArray = LongArray(4);
    weights[0] = 10L;
    weights[1] = 20L;
    weights[2] = 30L;
    weights[3] = 40L;

    val wrsResult: Int = random.wrsRandom(weights = weights);
    println("wrsResult : $wrsResult");

    val pityResult: Boolean = random.pityRandom(5, 10, 0);
    println("pityResult : $pityResult");
}