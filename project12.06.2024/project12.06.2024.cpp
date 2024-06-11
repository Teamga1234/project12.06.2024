#include "structs_of_info_disk.h"
#include <windows.h>
#include "Main_struct_of_song.h"
#include "Functions.h"
#include <fstream>
#include <cstring>


void ClearScreen()
{
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
int FindSongByName(struct song* arr, int size, const char* name)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(arr[i].song_title, name) == 0) {
            return i;
        }
    }
    return -1;
}

void sortbyprice(struct song* arr, const int size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].price_of_song < arr[j + 1].price_of_song) {
                song temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void deleteSong(song*& songs, int& size, unsigned int target_number) {
    int indexToDelete = -1;
    for (int i = 0; i < size; ++i) {
        if (songs[i].number_song == target_number) {
            indexToDelete = i;
            songs[i].type_song = 0;
            break;
        }
    }
    if (indexToDelete == -1) {
        cout << "Song with number " << target_number << " not found.\n";
        return;
    }
    for (int i = indexToDelete; i < size - 1; ++i) {
        songs[i] = songs[i + 1];

    }
    --size;

    song* newSongs = new song[size];
    memcpy(newSongs, songs, size * sizeof(song));
    delete[] songs;
    songs = newSongs;
    cout << "Song with number " << target_number << " deleted.\n";

}

void saveToFile(song* songs, int size, const char* filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; ++i) {
            file << songs[i].type_song << " "
                << songs[i].number_song << " "
                << songs[i].song_title << ";"
                << songs[i].author_name << ";"
                << songs[i].year_of_create << " "
                << songs[i].price_of_song << " "
                << songs[i].person_r.temp_owner << ";"
                << songs[i].person_r.address << ";"
                << songs[i].person_r.phone_temp_owner << ";"
                << songs[i].person_r.date_from.day << " "
                << songs[i].person_r.date_from.month << " "
                << songs[i].person_r.date_from.year << " "
                << songs[i].person_r.date_to.day << " "
                << songs[i].person_r.date_to.month << " "
                << songs[i].person_r.date_to.year << " "
                << songs[i].person_r.price_rental << " "
                << songs[i].person_o.owner_forever << ";"
                << songs[i].person_o.day_when_sold.day << " "
                << songs[i].person_o.day_when_sold.month << " "
                << songs[i].person_o.day_when_sold.year << " ";
        }
        file.close();
    }
}
void loadFromFile(song*& songs, int& size, const char* filename) {
    ifstream file(filename);
    if (file.is_open()) {
        file.seekg(0, ios::beg);
        songs = new song[size];
        for (int i = 0; i < size; ++i) {
            file >> songs[i].type_song
                >> songs[i].number_song;
            file.ignore(); 
            file.getline(songs[i].song_title, 25, ';');
            file.getline(songs[i].author_name, 50, ';');
            file >> songs[i].year_of_create
                >> songs[i].price_of_song;
            file.ignore(); 
            file.getline(songs[i].person_r.temp_owner, 100, ';');
            file.getline(songs[i].person_r.address, 50, ';');
            file.getline(songs[i].person_r.phone_temp_owner, 20, ';');
            file >> songs[i].person_r.date_from.day
                >> songs[i].person_r.date_from.month
                >> songs[i].person_r.date_from.year
                >> songs[i].person_r.date_to.day
                >> songs[i].person_r.date_to.month
                >> songs[i].person_r.date_to.year
                >> songs[i].person_r.price_rental;
            file.ignore(); 
            file.getline(songs[i].person_o.owner_forever, 100, ';');
            file >> songs[i].person_o.day_when_sold.day
                >> songs[i].person_o.day_when_sold.month
                >> songs[i].person_o.day_when_sold.year;
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

int main()
{

    
    int numbers_for_songs = 1;
    int size_of_songs = 2;
	int password = 1127251182;
	int password_try = 0;
	int selected_user = 0;
    song* SongsAll = nullptr;
    FILE* List_of_propose;
    FILE* Sizes2;
    FILE* Sizes;
    ifstream sizesFile("sizes.txt");
    if (sizesFile.is_open()) {
        sizesFile >> size_of_songs;
        sizesFile.close();
    }
    else {
        cout << "Unable to open sizes.txt for reading." << endl;
        size_of_songs = 0; 
    }
    ifstream sizes2File("sizes2.txt");
    if (sizes2File.is_open()) {
        sizes2File >> numbers_for_songs;
        sizes2File.close();
    }
    else {
        cout << "Unable to open sizes2.txt for reading." << endl;
        numbers_for_songs = 0;  
    }
    int index = -1;
    char temp_search[25] = "";
    char propose[85] = "";

    int what_find_need = 0;
    ChangeUser:
	cout << "+-------------------------------------------+\n";
	cout << "|Who are you                                |\n";
	cout << "|1)The buyer                                |\n";
	cout << "|2)The seller                               |\n";
	cout << "+-------------------------------------------+\n";
	cout << "|Today, renting any disk costs $1 for 1 day |\n";
	cout << "+-------------------------------------------+\n";
	tryAgain:
	cin >> selected_user;
	if (selected_user == 1)
	{
        ClearScreen();
        int menu = 0;
        do
        {
            cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++\n";
            cout << "|                     MENU                    |\n";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++++\n";
            cout << "| 0 - Exit                                    |\n";
            cout << "| 1 - Find song by name                       |\n";
            cout << "| 2 - Show all songs                          |\n";
            cout << "| 3 - Show all unused songs                   |\n";
            cout << "| 4 - Find songs by number                    |\n";
            cout << "| 5 - Buy the song by number                  |\n";
            cout << "| 6 - Rent a song by number                   |\n";
            cout << "| 7 - Sort all songs by price                 |\n";
            cout << "| 8 - Propose your song                       |\n";
            cout << "| 9 - Change user                             |\n";
            cout << "| 10 - MUST BE USED BEFORE USE                |\n";
            cout << "| 11 - MUST BE USED BEFORE CLOSING THE PROGRAM|\n";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++++\n";
            cin >> menu;

            switch (menu)
            {
            case 1:
                
                cout << "Enter name: ";
                cin.ignore();
                cin.getline(temp_search, 25);
                index = FindSongByName(SongsAll, size_of_songs, temp_search);
                if (index == -1) cout << "Not found " << temp_search << endl;
                else {
                    SongsAll[index].show_song_buy();
                }
                break;
            case 2:
                for (int i = 0; i < size_of_songs; i++)
                {
                    SongsAll[i].show_song_buy();
                }
                break;
            case 3:
                for (int i = 0; i < size_of_songs; i++)
                {
                    if (SongsAll[i].type_song == 0)
                    {
                        SongsAll[i].show_song_buy();
                    }
                    
                }
                break;
            case 4:
                cout << "Enter number of song: ";
                cin >> what_find_need;
                for (int i = 0; i < size_of_songs; i++)
                {
                    if (SongsAll[i].number_song == what_find_need)
                    {
                        SongsAll[i].show_song_buy();
                    }

                }

                break;
            case 5:
                cout << "Enter number of song: ";
                cin >> what_find_need;
                for (int i = 0; i < size_of_songs; i++)
                {
                    if (SongsAll[i].number_song == what_find_need && SongsAll[i].type_song==0)
                    {
                        SongsAll[i].type_song = 2;
                        SongsAll[i].person_o.fill_owner_form();
                    }

                }

                break;
            case 6:
                cout << "Enter number of song: ";
                cin >> what_find_need;
                for (int i = 0; i < size_of_songs; i++)
                {
                    if (SongsAll[i].number_song == what_find_need && SongsAll[i].type_song == 0)
                    {
                        SongsAll[i].type_song = 1;
                        SongsAll[i].person_r.fill_rental_form();
                    }

                }

                break;
            case 7:
                sortbyprice(SongsAll, size_of_songs);

                break;
            case 8:
                cout << "Enter your proposition(Name Author Year): ";
                cin.ignore();
                cin.getline(propose, 85);
                fopen_s(&List_of_propose, "propose.txt", "a+");
                fprintf(List_of_propose, "%s\n", propose);
                fclose(List_of_propose);

                break;
            case 9:
                goto ChangeUser;

                break;
            case 10:
                loadFromFile(SongsAll, size_of_songs, "songs.txt");

                break;
            case 11:
                saveToFile(SongsAll, size_of_songs, "songs.txt");
               
                break;
            default: cout << "Have a good day!!\n";   break;
            }

        } while (menu != 0);
	}
	else if (selected_user == 2)
	{
        ClearScreen();
		cout << "Enter password: ";
		cin >> password_try;
		if (password_try == password)
		{
            ClearScreen();
            int menu = 0;
            do
            {
                cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++\n";
                cout << "|                      MENU                     |\n";
                cout << "+++++++++++++++++++++++++++++++++++++++++++++++++\n";
                cout << "| 0 - Exit                                      |\n";
                cout << "| 1 - Add song                                  |\n";
                cout << "| 2 - Delete song (by number)                   |\n";
                cout << "| 3 - Delete forever owner (by number)          |\n";
                cout << "| 4 - Delete temp_owner at song (by number)     |\n";
                cout << "| 5 - Show all songs                            |\n";
                cout << "| 6 - Show all using songs                      |\n";
                cout << "| 7 - Find songs by name                        |\n";
                cout << "| 8 - Add temp_owner(rent) for song by number   |\n";
                cout << "| 9 - Add forever_owner(sell) for song by number|\n";
                cout << "| 10 - Show propositions                        |\n";
                cout << "| 11 - Change user                              |\n";
                cout << "| 12 - MUST BE USED BEFORE USE                  |\n";
                cout << "| 13 - MUST BE USED BEFORE CLOSING THE PROGRAM  |\n";
                cout << "+++++++++++++++++++++++++++++++++++++++++++++++++\n";
                cin >> menu;

                switch (menu)
                {
                case 1: 
                {
                    song a;
                    cout << "\nNEW SONG\n";
                    cin.ignore();
                    a.fill_song_form();
                    a.number_song = numbers_for_songs;
                    numbers_for_songs++;
                    addItemBack(SongsAll, size_of_songs, a);
                    ofstream sizes2File("sizes2.txt");
                    if (sizes2File.is_open()) {
                        sizes2File << numbers_for_songs;
                        sizes2File.close();
                    }
                    break;
                }
                case 2:
                    cout << "Enter number of song which need delete: ";
                    cin >> what_find_need;
                    deleteSong(SongsAll, size_of_songs, what_find_need);
                    break;
                case 3:
                    cout << "Enter number of song: ";
                    cin >> what_find_need;
                    for (int i = 0; i < size_of_songs; i++)
                    {
                        if (SongsAll[i].number_song == what_find_need)
                        {
                            SongsAll[i].type_song = 0;
                        }
                    }
                    break;
                case 4:
                    cout << "Enter number of song: ";
                    cin >> what_find_need;
                    for (int i = 0; i < size_of_songs; i++)
                    {
                        if (SongsAll[i].number_song == what_find_need)
                        {
                            SongsAll[i].type_song = 0;
                        }
                    }

                    break;
                case 5:
                    for (int i = 0; i < size_of_songs; i++)
                    {
                        SongsAll[i].show_song_admin();
                       
                    }

                    break;
                case 6:
                    for (int i = 0; i < size_of_songs; i++)
                    {
                        if (SongsAll[i].type_song == 1 || SongsAll[i].type_song == 2)
                        {
                            SongsAll[i].show_song_admin();
                        }
                        

                    }
                    cout << "\nif the list is empty, all songs are free\n";

                    break;
                case 7:
                    cout << "Enter name: ";
                    cin >> temp_search;
                    index = FindSongByName(SongsAll, size_of_songs, temp_search);
                    if (index == -1) cout << "Not found " << temp_search << endl;
                    else {
                        SongsAll[index].show_song_admin();
                    }

                    break;
                case 8:
                    cout << "Enter number of song: ";
                    cin >> what_find_need;
                    for (int i = 0; i < size_of_songs; i++)
                    {
                        if (SongsAll[i].number_song == what_find_need)
                        {
                            SongsAll[i].type_song = 1;
                            SongsAll[i].person_r.fill_rental_form();
                        }
                    }

                    break;
                case 9:
                    cout << "Enter number of song: ";
                    cin >> what_find_need;
                    for (int i = 0; i < size_of_songs; i++)
                    {
                        if (SongsAll[i].number_song == what_find_need)
                        {
                            SongsAll[i].type_song = 2;
                            SongsAll[i].person_o.fill_owner_form();
                        }
                    }

                    break;
                case 10:
                    fopen_s(&List_of_propose, "propose.txt", "r");
                    while (fgets(propose, sizeof(propose), List_of_propose) != nullptr) {
                        cout << propose;
                    }
                    fclose(List_of_propose);
                    break;
                case 11:
                    goto ChangeUser;

                    break;
                case 12:
                    loadFromFile(SongsAll, size_of_songs, "songs.txt");
                    
                    break;
                case 13:
                    saveToFile(SongsAll, size_of_songs, "songs.txt");
                    fopen_s(&Sizes2, "sizes2.txt", "w");
                    fprintf(Sizes2, "%d", numbers_for_songs);
                    fclose(Sizes2);
                    fopen_s(&Sizes, "sizes.txt", "w");
                    fprintf(Sizes, "%d", size_of_songs);
                    fclose(Sizes);
                    
                    break;
                default: cout << "Have a good day!!\n";   break;
                }

            } while (menu != 0);
		}
		else
			cout << "Wrong password!\n";
	}
	else
		goto tryAgain;



}
