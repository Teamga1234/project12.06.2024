#include "structs_of_info_disk.h"
#include <windows.h>
#include "Main_struct_of_song.h"
#include "Functions.h"
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
//Сортування масиву
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

int main()
{

    //song to_first{
    //type_song = 0; //0 - free, 1 - rent, 2 - sold
    //number_song = 0;
    //song_title[25] = "";
    //author_name[50] = "";
    //year_of_create = 2024;
    //price_of_song = 0;
    //person_r = { "", "", "", {0, 0, 0}, {0, 0, 0}, 0 };
    //person_o = { "", {0, 0, 0} };
    //};
    int numbers_for_songs = 1;
    int size_of_songs = 0;
	int password = 1127251182;
	int password_try = 0;
	int selected_user = 0;
    song* SongsAll = nullptr;
    FILE* Music_Room_all_info = nullptr;
    FILE* List_of_propose = nullptr;
    FILE* Sizes = nullptr;



    int index = -1;
    char temp_search[25] = "";
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
            cout << "| 1 - Find songs by name                      |\n";
            cout << "| 2 - Show all songs                          |\n";
            cout << "| 3 - Show all unused songs                   |\n";
            cout << "| 4 - Find songs by number                    |\n";
            cout << "| 5 - Buy the song by number                  |\n";
            cout << "| 6 - Rent a song by number                   |\n";
            cout << "| 7 - Sort all songs by price                 |\n";
            cout << "| 8 - Propose your song                       |\n";
            cout << "| 9 - Change user                             |\n";
            cout << "+++++++++++++++++++++++++++++++++++++++++++++++\n";
            cin >> menu;

            switch (menu)
            {
            case 1:
                
                cout << "Enter name: ";
                cin.getline(temp_search, 25);
                FindSongByName(SongsAll, size_of_songs, temp_search);
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


                break;
            case 9:
                goto ChangeUser;

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
                    break;
                }
                case 2:
                    
                    break;
                case 3:
                    
                    break;
                case 4:
                    

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


                    break;
                case 9:


                    break;
                case 10:


                    break;
                case 11:
                    goto ChangeUser;

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
