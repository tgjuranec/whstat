// Jenkinsfile (Declarative Pipeline)
/* Requires the Docker Pipeline plugin */
pipeline {
    agent { docker { image 'gcc:latest' } }
    stages {
        stage('build') {
            steps {
		gcc --version
                g++ -o whstat --static whquote.cpp
            }
        }
    }
}
