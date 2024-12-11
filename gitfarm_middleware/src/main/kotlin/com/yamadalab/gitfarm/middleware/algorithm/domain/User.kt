package com.yamadalab.gitfarm.middleware.algorithm.domain

data class User(
    val name: String,
    var failCount: Int
) {
}