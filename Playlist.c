#include <stdio.h>      // Standard I/O library for input and output functions
#include <string.h>     // String manipulation library

#include <stdlib.h>     // Standard library for memory allocation and other utilities

#include <time.h>       // Time library for time-related functions

 

void sortArtists(char sortedArtists[][80], char artists[][80], int numOfArtists);

// Function prototype for sorting artists alphabetically

void sortSongs(char songsByArtist[][3][80], int numOfArtists, int numSongsPerArtist[]);

// Function prototype for sorting songs alphabetically for each artist

void shuffleSongs(char shuffledSongs[][80], int numOfArtists, char songsByArtist[][3][80], int *numOfSongs, int shuffle);

// Function prototype for shuffling songs

void getArtistsAndSongs(char artists[][80], char songsByArtist[][3][80], int *numOfArtists, int numSongsPerArtist[]);

// Function prototype for getting artists and their songs from user input

 

int main(void) {

    char artists[4][80];                // Array to store artists' names

    char sortedArtists[4][80];          // Array to store sorted artists' names

    char songsByArtist[4][3][80];       // Array to store songs for each artist

    char shuffledSongs[24][80];         // Array to store shuffled songs

    int numOfArtists = 0;               // Counter for total number of artists

    int numSongsPerArtist[4];           // Array to store total number of songs for each artist

    int numOfSongs = 0;                 // Counter for total number of songs

    int shuffle = 1;                    // Control variable for shuffling, set to 1 by default

 

    getArtistsAndSongs(artists, songsByArtist, &numOfArtists, numSongsPerArtist);

    // Function call to get artists and songs from user input

    sortArtists(sortedArtists, artists, numOfArtists);

    // Function call to sort artists alphabetically

    sortSongs(songsByArtist, numOfArtists, numSongsPerArtist);

    // Function call to sort songs alphabetically for each artist

    shuffleSongs(shuffledSongs, numOfArtists, songsByArtist, &numOfSongs, shuffle);

    // Function call to shuffle songs

 

    printf("\nSorted Artists and Songs:\n");

    // Print sorted artists and their songs

    for (int i = 0; i < numOfArtists; i++) {

        printf("\nArtist: %s\n", sortedArtists[i]);

        for (int j = 0; j < numSongsPerArtist[i]; j++) {

            printf("Song %d: %s\n", j + 1, songsByArtist[i][j]);

        }

    }

 

    printf("\nPlaylist: \n");

    printf("--------------------------------------------------\n");

    printf("| %-20s | %-30s |\n", "Song Index", "Song Title");

    printf("--------------------------------------------------\n");

 

    int playedIndices[12] = {0};        // Array to keep track of played songs

    for (int i = 0; i < numOfSongs * 2; i++) {

        int index;

        if (i < numOfSongs) {

            index = i % numOfSongs;

        } else {

            do {

                index = rand() % numOfSongs;

            } while (playedIndices[index] == 1);

            playedIndices[index] = 1;

        }

        if (shuffledSongs[index][0] != '\0') {

            printf("| %-20d | %-30s |\n", i + 1, shuffledSongs[index]);

        }

    }

    printf("--------------------------------------------------\n");

    return 0;

}

 

void sortArtists(char sortedArtists[][80], char artists[][80], int numOfArtists) {

    // Copy artists array to sortedArtists

    for (int i = 0; i < numOfArtists; i++) {

        strcpy(sortedArtists[i], artists[i]);

    }

    // Sorting sortedArtists via bubble sort

    int i, j;

    char swap[80];

    for (i = 0; i < numOfArtists - 1; i++) {

        for (j = 0; j < numOfArtists - i - 1; j++) {

            if (strcmp(sortedArtists[j], sortedArtists[j + 1]) > 0) {

                strcpy(swap, sortedArtists[j]);

                strcpy(sortedArtists[j], sortedArtists[j + 1]);

                strcpy(sortedArtists[j + 1], swap);

            }

        }

    }

}

 

void sortSongs(char songsByArtist[][3][80], int numOfArtists, int numSongsPerArtist[]) {

    // Sorting songs of each artist alphabetically

    int i, j, k;

    char swap[80];

    for (i = 0; i < numOfArtists; i++) {

        for (j = 0; j < numSongsPerArtist[i] - 1; j++) {

            for (k = 0; k < numSongsPerArtist[i] - j - 1; k++) {

                if (strcmp(songsByArtist[i][k], songsByArtist[i][k + 1]) > 0) {

                    strcpy(swap, songsByArtist[i][k]);

                    strcpy(songsByArtist[i][k], songsByArtist[i][k + 1]);

                    strcpy(songsByArtist[i][k + 1], swap);

                }

            }

        }

    }

}

 

void shuffleSongs(char shuffledSongs[][80], int numOfArtists, char songsByArtist[][3][80], int *numOfSongs, int shuffle) {

    int z = 0;

    *numOfSongs = 0;

    // Copy songs to shuffledSongs array and count total number of songs

    for (int i = 0; i < numOfArtists; i++) {

        for (int j = 0; j < 3; j++) {

            if (songsByArtist[i][j][0] != '\0') {

                strcpy(shuffledSongs[z], songsByArtist[i][j]);

                z++;

                (*numOfSongs)++;

            }

        }

    }

    // Perform shuffling if enabled

    if (shuffle) {

        srand(time(NULL));      // Seed random number generator with current time

        for (int i = *numOfSongs - 1; i > 0; i--) {

            int j = rand() % (i + 1);

            char temp[80];

            strcpy(temp, shuffledSongs[i]);

            strcpy(shuffledSongs[i], shuffledSongs[j]);

            strcpy(shuffledSongs[j], temp);

        }

    }

}

 

void getArtistsAndSongs(char artists[][80], char songsByArtist[][3][80], int *numOfArtists, int numSongsPerArtist[]) {

    char buffer[80];

    // Initialize numSongsPerArtist array to zero

    for (int i = 0; i < 4; i++) {

        numSongsPerArtist[i] = 0;

    }

    // Get artists and their songs from user input

    for (int i = 0; i < 4; i++) {

        printf("\nEnter the name of an artist (Press Enter to stop): ");

        fgets(buffer, sizeof(buffer), stdin);

        size_t len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {

            buffer[len - 1] = '\0';

        }

        if (strlen(buffer) == 0) {

            break;

        }

        strcpy(artists[i], buffer);

 

        for (int j = 0; j < 3; j++) {

            printf("Enter song %d for %s (Press Enter to stop): ", j + 1, artists[i]);

            fgets(buffer, sizeof(buffer), stdin);

            len = strlen(buffer);

            if (len > 0 && buffer[len - 1] == '\n') {

                buffer[len - 1] = '\0';

            }

            if (strlen(buffer) == 0) {

                break;

            }

            strcpy(songsByArtist[*numOfArtists][j], buffer);

            numSongsPerArtist[*numOfArtists]++;

        }

        (*numOfArtists)++;

    }

}