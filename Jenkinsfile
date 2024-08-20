// Jenkinsfile (Declarative Pipeline)
/* Requires the Docker Pipeline plugin */
pipeline {
    agent { docker { image 'gcc:latest' } }
    stages {
        stage('build') {
            steps {
                sh 'g++ -o whstat --static whquote.cpp'
            }
        }
    }
}
