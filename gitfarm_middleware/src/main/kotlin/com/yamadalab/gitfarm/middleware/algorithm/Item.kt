package com.yamadalab.gitfarm.middleware.algorithm;

data class Item(
    val id: String,
    val weight: Int,
    val probability: Double,
    val failCount: Int
) {

}