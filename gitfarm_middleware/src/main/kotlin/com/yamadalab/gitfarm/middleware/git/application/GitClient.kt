package com.yamadalab.gitfarm.middleware.git.application;

import com.yamadalab.gitfarm.middleware.git.domain.GitConstants
import com.yamadalab.gitfarm.middleware.git.domain.GitUser
import com.yamadalab.gitfarm.middleware.utils.Utils
import io.ktor.client.*
import io.ktor.client.engine.cio.*
import io.ktor.client.plugins.contentnegotiation.*
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import io.ktor.serialization.kotlinx.json.*
import kotlinx.serialization.json.Json

class GitClient {

    private var token: String? = null;
    private var client: HttpClient? = null;

    init {
        this.client = HttpClient(CIO) {
            install(ContentNegotiation) {
                json()
            }
        }

        this.token = Utils.loadTokenByYaml(GitConstants.GITHUB_TOKEN_YAML_NAME);
    }

    private fun getClient(): HttpClient {
        return this.client!!;
    }

    suspend fun getTotalContributionsByYear(user: String, year: String): Int {
        val requestBody: Map<Any, Any> = mapOf(
            "query" to Utils.loadGraphQL(GitConstants.GITHUB_GRAPHQL_CONTRIBUTION_BY_YEAR_NAME)
                .replaceFirst(GRAPHQL_USER_VAL, user)
                .replace(GRAPHQL_YEAR_VAL, year)
        );

        val response: HttpResponse = this.getClient().post(GitConstants.GITHUB_GRAPHQL_API_URL) {
            headers {
                append(HttpHeaders.Accept, GitConstants.KTOR_HTTP_ACCEPT_TYPE);
                append(HttpHeaders.Authorization, "Bearer $token");
                append(HttpHeaders.ContentType, ContentType.Application.Json.toString());
                append(GitConstants.KTOR_HTTP_USER_AGENT[0], GitConstants.KTOR_HTTP_USER_AGENT[1]);
            }
            setBody(requestBody)
        }
        this.getClient().close();

        val gitUser: GitUser = Json.decodeFromString(response.bodyAsText());
        return gitUser.data.user.contributionsCollection.contributionCalendar.totalContributions;
    }

    companion object {
        private const val GRAPHQL_USER_VAL = "\${name}";
        private const val GRAPHQL_YEAR_VAL = "\${year}";
    }
}