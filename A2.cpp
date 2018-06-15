{\rtf1\ansi\ansicpg1252\deff0\nouicompat\deflang1033{\fonttbl{\f0\fnil\fcharset0 Courier New;}{\f1\fnil\fcharset0 Calibri;}}
{\*\generator Riched20 6.3.9600}\viewkind4\uc1 
\pard\sl276\slmult1\f0\fs22\lang9 /*\par
 * Peter De Jesus (cssc1096) & Yonas Lemmi (cssc1097)\par
 * CS570 - Operating Systems, Summer 2017\par
 * Assignment #2 - Page Replacement Algorithm\par
 *\par
 * This program will take the numbers from a text file which\par
 * represent page numbers and put them into a vector, then those\par
 * numbers will be process using OPT, Clock, and Second Chance\par
 * Page Replacement Algorithms to get the page faults for each\par
 * of the algorithms\par
 */\par
\par
#include "A2.h"\par
\par
int main() \{\par
\par
        cout << "Enter the number of frames: ";\par
        cin >> num_of_frames;\par
\par
        if (get_numbers()==1) \{\par
                return 1;\par
        \}\par
        cout << "Page Faults:" << endl;\par
        cout << "Second Chance: " << second_chance(numbers,num_of_frames);\par
        cout << endl;\par
        cout << "OPT: " << opt(numbers, num_of_frames) << endl;\par
        cout << "Clock: " << clock(numbers, num_of_frames) << endl;\par
\par
        return 0;\par
\}\par
\par
/*\par
 * This will get the numbers from a text file and put them in\par
 * a vector\par
 */\par
int get_numbers() \{\par
\par
        in.open("pages.txt", ios::in);\par
        if(!in) \{\par
                cout << "File not found" << endl;\par
                return 1;\par
        \}\par
        while (getline(in,line)) \{\par
                put = line;\par
        \}\par
\par
        stringstream ss(put);\par
        int temp;\par
        while (ss >> buffer) \{\par
                temp = atoi(buffer.c_str());\par
                numbers.push_back(temp);\par
        \}\par
        return 0;\par
\}\par
\par
/*\par
 * This will process the page numbers using the OPT Page\par
 * Replacement Algorithm and returns the page faults found\par
 */\par
                                //input\par
int opt(vector<int> pages, int frame_num) \{\par
        int countsize = pages.size();\par
        int number[frame_num];  // create frame\par
        int page_faults = 0;    // counter for page faults\par
\par
        // initialize the frames\par
        for (int i = 0; i < frame_num; i++) \{\par
                number[i] = -1;\par
        \}\par
\par
        int inserting = 0;      // number we insert next\par
        bool status = false;    // if number is already in frame\par
\par
        int tracker1 = 0;       // tracker for furthest number\par
        int farthest = 0;\par
        int index = 0;\par
        bool found = false;     // tracker if number is not in future\par
\par
        int offset = 1;\par
\par
        // insert numbers in frames\par
        for (int i = 0; i < countsize; i++) \{\par
                farthest = 0;\par
                tracker1 = 0;\par
\par
                inserting = pages.at(i);        //get next number to insert\par
                status = false;         //not yet found\par
\par
                // search for duplicates in frame\par
                for (int j = 0; j < frame_num; j++) \{\par
                        if (inserting==number[j]) \{\par
                                status = true;\par
                                break;\par
                        \}\par
                \}\par
                // if number is in frame, go to next number\par
                if (status==true) \{\par
                        offset++;\par
                        continue;\par
                \}\par
                page_faults++;  // fault since number is not in frame\par
\par
                for (int j = 0; j < frame_num; j++) \{\par
                        found = false;\par
\par
                        // deal with empty frames\par
                        if (number[j]==-1) \{\par
                                index = j;\par
                                break;\par
                        \}\par
                        // check each frames\par
                        for (int k = i+1; k < countsize; k++) \{\par
                                if (number[j]==pages.at(k)) \{\par
                                        found = true;\par
                                        tracker1 = k;\par
                                        break;\par
                                \}\par
                        \}\par
                        if (found==true) \{\par
                                if (farthest < tracker1) \{\par
                                        farthest = tracker1;\par
                                        index = j;\par
                                \}\par
                        \} else \{\par
                                farthest = countsize;\par
                                index = j;\par
                                break;\par
                        \}\par
\par
                \}\par
                offset++;\par
                number[index] = inserting;\par
        \}\par
        return page_faults;\par
\}\par
\par
/*\par
 * This will take the page number and process them by using\par
 * the Second Chance Page Replacement Algorithm and it will\par
 * return the page fault found\par
 */\par
                                        //input\par
int second_chance(vector<int> pages, int frame_num) \{\par
\par
        int page_fault = 0;\par
        int countsize = pages.size();\par
\par
        // create the frames needed\par
        int number[frame_num];\par
        int chance[frame_num];\par
\par
        // initialize the number and chance frames\par
        for (int x = 0; x < frame_num; x++) \{\par
                number[x] = 0;\par
                chance[x] = 0;\par
        \}\par
\par
        // variables needed for the second chance\par
        int tracker = 0;\par
        int tracker2 = 0;\par
        bool found = false;\par
        bool emptyframe = false;\par
        int index = 0;\par
        int inserting = 0;      //number that will be inserted\par
\par
        // insert the number\par
        for (int i = 0; i < countsize; i++) \{\par
\par
                inserting = pages.at(i);\par
\par
                //check if the number is in the frames\par
                found = false;\par
                for (int j = 0; j < frame_num; j++) \{\par
                        if (number[j]==inserting) \{\par
                                chance[j] = 1;\par
                                found = true;\par
                                break;\par
                        \}\par
                \}\par
                // if duplicate is found, go to next number\par
                if (found==true) continue;\par
                // if no duplicate, page fault occurs\par
                page_fault++;\par
\par
                // deal with empty frames\par
                for (int j = 0; j < frame_num; j++) \{\par
                        emptyframe = false;\par
                        if (number[j]==0) \{\par
                                number[j] = inserting;\par
                                emptyframe = true;\par
                                break;\par
                        \}\par
                \}\par
                // if we insert number in empty frame, go to next number\par
                if (emptyframe==true) continue;\par
\par
                if (tracker==frame_num) tracker = 0;\par
\par
                if (chance[tracker]==1) \{\par
                        tracker2 = tracker;\par
                        for (int k = 0; k < frame_num; k++) \{\par
                                if (tracker2==frame_num) tracker2 = 0;\par
                                if (chance[tracker2]==0) \{\par
                                        index = tracker2;\par
                                \} else \{\par
                                        chance[tracker2] = 0;\par
                                        tracker2++;\par
                                \}\par
                        \}\par
                        // update the oldest\par
                        for (int k = index; k < frame_num; k++) \{\par
                                if ((k+1)==frame_num) break;\par
                                number[k] = number[k+1];\par
                                chance[k] = chance[k+1];\par
                        \}\par
                        number[frame_num - 1] = inserting;\par
                \} else \{\par
                        for (int k = tracker; k < frame_num; k++) \{\par
                                if ((k+1)==frame_num) break;\par
                                number[k] = number[k+1];\par
                                chance[k] = chance[k+1];\par
                        \}\par
                        number[frame_num - 1] = inserting;\par
                \}\par
\par
        \}\par
\par
        return page_fault;\par
\}\par
\par
/*\par
 * This will take the page numbers and process them using the\par
 * Clock Page Replacement Algorithm and returns the page fault\par
 * found\par
 */\par
                                // input\par
int clock(vector<int> pages, int frame_num) \{\par
\par
        int countsize = pages.size();   // amount of numbers\par
        int page_faults = 0;\par
        // create clock frame\par
        int number[frame_num];\par
        int bit[frame_num];\par
\par
        // initialize frames\par
        for (int i = 0; i < frame_num; i++) \{\par
                number[i] = 0;\par
                bit[i] = 0;\par
        \}\par
        // variables for the clock\par
        int hand = 0;           // clock hand pointer\par
        int inserting = 0;      // number to insert to frame\par
        bool found = false;     // tracker to see if number is in frame\par
\par
        // insert number\par
        for (int i = 0; i < countsize; i++) \{\par
                inserting = pages.at(i);\par
                found = false;\par
                //look for duplicate in frame\par
                for (int j = 0; j < frame_num; j++) \{\par
                        if(number[j]==inserting) \{\par
                                found = true;\par
                                bit[j] = 1;\par
                                break;\par
                        \}\par
                \}\par
                // if number is in frames, go to the next number to insert\par
                if (found==true) continue;\par
\par
                // since number is not in frame, we have page fault.\par
                page_faults++;\par
\par
                // if number is not in the frame, insert it\par
                for (int j = 0; j <= frame_num; j++) \{\par
                        if (hand==frame_num) hand = 0;\par
                        if (bit[hand]==1) \{\par
                                bit[hand] = 0;\par
                                hand++;\par
                        \} else \{\par
                                number[hand] = inserting;\par
                                bit[hand] = 1;\par
                                hand++;\par
                                break;\par
                        \}\par
                \}\par
        \}\par
        return page_faults;\par
\}\f1\par
}
 