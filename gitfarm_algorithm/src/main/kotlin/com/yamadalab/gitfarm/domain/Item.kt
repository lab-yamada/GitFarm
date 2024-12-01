package com.yamadalab.gitfarm.domain

data class Item(
    val id: String,
    val weight: Int,
    val probability: Double,
    val failCount: Int
) {

}