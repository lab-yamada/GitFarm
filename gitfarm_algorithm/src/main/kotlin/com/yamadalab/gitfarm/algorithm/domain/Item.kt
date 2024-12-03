package com.yamadalab.gitfarm.algorithm.domain

data class Item(
    val id: String,
    val weight: Int,
    val probability: Double,
    val failCount: Int
) {

}