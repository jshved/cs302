# Project 1 - Parsing Music Files/Data

**[Project 1 Write Up](https://web.eecs.utk.edu/~semrich/ds20/assignments/proj01.html)**

    // lib_info.cpp
    // Project 1
    // Authors: Grant Anderson, Logan Tillman  
    // Date: January 22, 2020  
    /*  
      This program parses through a text file containing information about various artists
      and their works. It keeps track of every song for an album, and it keeps a running total
      of the time for each song, album, and artist.
    */

Our program `lib_info` will parse music data given in the following format

    Back_In_Black 4:15 AC_DC Back_In_Black Rock 6
    Larks'_Tongues_In_Aspic,_Part_III 5:56 King_Crimson Three_of_a_Perfect_Pair Rock 9
    Ravel,_Menuet_Antique 5:28 Casadesus,_Robert Ravel,_Complete_Piano_Music,_Disc_2 Classical 8
    Pungee 3:02 Meters,_The Look-Ka_Py_Py Rock 3
    Naima 4:24 Coltrane,_John Giant_Steps Jazz 6
    Rachmaninoff,_Piano_Concerto_#3_in_Dm,_Opus_30,_2._Intermezzo_-_Adagio 11:43 Berman,_Lazar Rachmaninoff_-_Piano_Concerto_#3 Classical 2
    Grieg,_Norwegian_Melodie,_EG_108,_#44,_Sailor's_Song_-_Hurrah_For_Jonas_Anton_Hjelm 0:32 Steen-Nokleberg,_Einar Grieg_Piano_Music,_Volume_05 Classical 45
    Beethoven,_Sonata_#12_in_Ab,_Opus_26,_2._Scherzo._Allegro_molto 2:51 Richter,_Sviatoslav Russian_Piano_School,_V06 Classical 9
    Your_Cheatin'_Heart 2:44 Armstrong,_Louis Highlights_From_His_Decca_Years,_Disc_2 Jazz 11
    Pieces_Of_Dreams 5:19 Turrentine,_Stanley More_Than_A_Mood Jazz 6

Running `lib_info` on the `.txt` file will produce the following output

    UNIX> lib_info Small.txt
    Coltrane, John: 4, 18:37
            Giant Steps: 4, 18:37
                    1. Giant Steps: 4:46
                    3. Countdown: 2:25
                    6. Naima: 4:24
                    7. Mr. P.C.: 7:02
    Lyle, Bobby: 1, 5:16
            Night Breeze: 1, 5:16
                    5. Naima: 5:16
    Puente, Tito: 1, 4:02
            El Rey: 1, 4:02
                    5. Giant Steps: 4:02
    Tjader, Cal: 1, 5:36
            A Fuego Vivo: 1, 5:36
                    6. Naima: 5:36
    Walton, Cedar: 4, 30:44
            Eastern Rebellion: 1, 8:38
                    2. Naima: 8:38
            Naima: 3, 22:06
                    2. This Guy's In Love With You: 8:10
                    4. Down In Brazil: 6:07
                    6. Naima: 7:49
    UNIX>


## Compile Instructions

Typing `make` in the base directory of the project will compile all of the `.cpp` and `.hpp` files.

`$ ~/project01> make`


## Running the Program

`$ ~/project01> ./lib_info file.txt`
