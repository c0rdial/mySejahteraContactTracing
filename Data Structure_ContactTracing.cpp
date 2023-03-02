// Data Structure Assignment
// Wan Mohammed Adam
// 
// Venue ID (0. Sunway Pyramid | 1.UoWMKDU | 2.Family Mart)
// Risk Status (1.Low Risk | 2.Infected | 3. Close Contact)
// Vacc Status (1.Fully Vaccinated | 2.Partially Vaccinated | 3.Unvacicnated)
// Ethnicity (1.Malay | 2.Chinese | 3.Indian | 4.Others)
// Relation (1.Spouse|2.Child|3.Siblings|4.Parents/Parent-in-law|5.Grandparents|6.Guardians|7.Others)
// Within 24 hours is considered as close contact

#define _CRT_SECURE_NO_WARNINGS 
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
using timestamp = time_t;

// Assume 3 venues only
const int VENUESIZE = 3;

struct Dependent {
   string fullName = "";
   int relation = 0;
   string IC = "";
   int age = 0;
   char gender = ' ';
   string currentAddress = "";
   int riskStatus = 0;
};

struct User {
   string id = "", name = "", identityNum = "";
   int age = 0, ethnic = 0;
   string address = "";
   char gender = ' ';
   string password = "";
   int vaccStatus = 0, riskStatus = 0;

   Dependent dep[2];

   User* nextUser;
}*userHead, * userTail;

// Stores Check-in history of each Venue seperately
struct VenueCheckInHistory {
   string userID = "";
   int usrRiskStat = 0;
   string dateTime = "";
   bool dependentTrace[2] = { false, false };
   int depRiskStat[2] = { 0, 0 };

   VenueCheckInHistory* nextVenueCheckIn;
} *venueTop[VENUESIZE];

// Stores Check-in history of the System User
struct UserCheckInHistory {
   VenueCheckInHistory userCheckInHistory;
   int venueID = 0;

   UserCheckInHistory* nextUserCheckIn;
}*userTop;

// Stores ALL Check-in history 
struct MainCheckInHistory {
   UserCheckInHistory mainCheckInHistory;

   MainCheckInHistory* nextMainCheckIn;
}*mainTop;

// Stores Close Contact List
struct CloseContact {
   string name = "";

   CloseContact* nextCloseCon;
}*closeConHead[VENUESIZE];


// HARD CODE
//------------------------------------------------------------------------------------------------------------ - */
// Hard code 5 user for demonstration
void hardCodeUser()
{
   //This user will be hard coded as infecetd
   User* systemUser = new User;
   systemUser->id = "0194143449";
   systemUser->name = "Bryan Lee";
   systemUser->identityNum = "010916-10-0963";
   systemUser->age = 21;
   systemUser->ethnic = 1;
   systemUser->address = "13, Jalan Zapin, 3B";
   systemUser->gender = 'M';
   systemUser->password = "password1";
   systemUser->vaccStatus = 1;
   systemUser->riskStatus = 2; // Assume this user is infected
   systemUser->nextUser = NULL;
   userHead = systemUser;
   userTail = systemUser;

   User* systemUser1 = new User;
   systemUser1->id = "stevejobs@apple.com";
   systemUser1->name = "Steve Jobs";
   systemUser1->identityNum = "670918-07-1061";
   systemUser1->age = 45;
   systemUser1->ethnic = 2;
   systemUser1->address = "574 Parkway Drive";
   systemUser1->gender = 'M';
   systemUser1->password = "password2";
   systemUser1->vaccStatus = 1;
   systemUser1->riskStatus = 1; // Demonstration Line 2
   systemUser1->nextUser = NULL;
   userTail->nextUser = systemUser1;
   userTail = systemUser1;

   User* systemUser2 = new User;
   systemUser2->id = "0123451215";
   systemUser2->name = "Hanna Amirah";
   systemUser2->identityNum = "960205-22-0963";
   systemUser2->age = 26;
   systemUser2->ethnic = 2;
   systemUser2->address = "56, Jalan Zaaba, TTDI";
   systemUser2->gender = 'M';
   systemUser2->password = "password123";
   systemUser2->vaccStatus = 1;
   systemUser2->riskStatus = 1;
   systemUser2->nextUser = NULL;
   userTail->nextUser = systemUser2;
   userTail = systemUser2;

   User* systemUser3 = new User;
   systemUser3->id = "drealok@gmail.com";
   systemUser3->name = "Andrea Lok";
   systemUser3->identityNum = "941020-07-6781";
   systemUser3->age = 21;
   systemUser3->ethnic = 1;
   systemUser3->address = "C-2 Stories of Taman Tunku";
   systemUser3->gender = 'F';
   systemUser3->password = "password356";
   systemUser3->vaccStatus = 1;
   systemUser3->riskStatus = 1;
   systemUser3->nextUser = NULL;
   userTail->nextUser = systemUser3;
   userTail = systemUser3;

   User* systemUser4 = new User;
   systemUser4->id = "0134893256";
   systemUser4->name = "Brandon James";
   systemUser4->identityNum = "010826-56-0983";
   systemUser4->age = 21;
   systemUser4->ethnic = 1;
   systemUser4->address = "13, Jalan zapin, 3A";
   systemUser4->gender = 'M';
   systemUser4->password = "password5";
   systemUser4->vaccStatus = 1;
   systemUser4->riskStatus = 1;
   systemUser4->nextUser = NULL;
   userTail->nextUser = systemUser4;
   userTail = systemUser4;
}

// Hard code check in history for demonstration
void hardCodeCheckInHistory()
{
   // Hard Code CheckIn History 0
   MainCheckInHistory* mainHistory = new MainCheckInHistory;
   mainHistory->mainCheckInHistory.userCheckInHistory.dateTime = "2022-03-22,17:47:52";
   mainHistory->mainCheckInHistory.userCheckInHistory.userID = "0134893256";
   mainHistory->mainCheckInHistory.venueID = 0;
   mainHistory->mainCheckInHistory.userCheckInHistory.usrRiskStat = 1;
   mainHistory->nextMainCheckIn = NULL;
   mainTop = mainHistory;

   VenueCheckInHistory* venueHistory[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       venueHistory[i] = new VenueCheckInHistory;
   }
   venueHistory[0]->dateTime = "2022-03-22,17:47:52";
   venueHistory[0]->userID = "0134893256";
   venueHistory[0]->usrRiskStat = 1;
   venueHistory[0]->nextVenueCheckIn = NULL;
   venueTop[0] = venueHistory[0];


   // Hard Code CheckIn History 1
   MainCheckInHistory* mainHistory1 = new MainCheckInHistory;
   mainHistory1->mainCheckInHistory.userCheckInHistory.dateTime = "2022-03-22,14:47:52"; // Demonstration 2
   mainHistory1->mainCheckInHistory.userCheckInHistory.userID = "stevejobs@apple.com";
   mainHistory1->mainCheckInHistory.venueID = 1;
   mainHistory1->mainCheckInHistory.userCheckInHistory.usrRiskStat = 1;
   mainHistory1->nextMainCheckIn = NULL;
   mainHistory1->nextMainCheckIn = mainTop;
   mainTop = mainHistory1;

   VenueCheckInHistory* venueHistory1[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       venueHistory1[i] = new VenueCheckInHistory;
   }
   venueHistory1[1]->dateTime = "2022-03-22,14:47:52"; // Demonstration 2
   venueHistory1[1]->userID = "stevejobs@apple.com";
   venueHistory1[1]->usrRiskStat = 1;
   venueHistory1[1]->nextVenueCheckIn = NULL;
   venueHistory1[1]->nextVenueCheckIn = venueTop[1];
   venueTop[1] = venueHistory1[1];


   // Hard Code CheckIn History 2
   MainCheckInHistory* mainHistory2 = new MainCheckInHistory;
   mainHistory2->mainCheckInHistory.userCheckInHistory.dateTime = "2022-03-22,15:47:52";
   mainHistory2->mainCheckInHistory.userCheckInHistory.userID = "drealok@gmail.com";
   mainHistory2->mainCheckInHistory.venueID = 2;
   mainHistory2->mainCheckInHistory.userCheckInHistory.usrRiskStat = 1;
   mainHistory2->nextMainCheckIn = NULL;
   mainHistory2->nextMainCheckIn = mainTop;
   mainTop = mainHistory2;

   VenueCheckInHistory* venueHistory2[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       venueHistory2[i] = new VenueCheckInHistory;
   }
   venueHistory2[2]->dateTime = "2022-03-22,15:47:52";
   venueHistory2[2]->userID = "drealok@gmail.com";
   venueHistory2[2]->usrRiskStat = 1;
   venueHistory2[2]->nextVenueCheckIn = NULL;
   venueHistory2[2]->nextVenueCheckIn = venueTop[2];
   venueTop[2] = venueHistory2[2];


   // Hard Code CheckIn History 3
   MainCheckInHistory* mainHistory3 = new MainCheckInHistory;
   mainHistory3->mainCheckInHistory.userCheckInHistory.dateTime = "2022-03-22,16:47:52";
   mainHistory3->mainCheckInHistory.userCheckInHistory.userID = "0123451215";
   mainHistory3->mainCheckInHistory.venueID = 2;
   mainHistory3->mainCheckInHistory.userCheckInHistory.usrRiskStat = 1;
   mainHistory3->nextMainCheckIn = NULL;
   mainHistory3->nextMainCheckIn = mainTop;
   mainTop = mainHistory3;

   VenueCheckInHistory* venueHistory3[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       venueHistory3[i] = new VenueCheckInHistory;
   }
   venueHistory3[2]->dateTime = "2022-03-22,16:47:52";
   venueHistory3[2]->userID = "0123451215";
   venueHistory3[2]->usrRiskStat = 1;
   venueHistory3[2]->nextVenueCheckIn = NULL;
   venueHistory3[2]->nextVenueCheckIn = venueTop[2];
   venueTop[2] = venueHistory3[2];


   // Hard Code CheckIn History 4
   MainCheckInHistory* mainHistory4 = new MainCheckInHistory;
   mainHistory4->mainCheckInHistory.userCheckInHistory.dateTime = "2022-04-10,17:47:52"; //Demonstration
   mainHistory4->mainCheckInHistory.userCheckInHistory.userID = "0194143449";
   mainHistory4->mainCheckInHistory.venueID = 0;
   mainHistory4->mainCheckInHistory.userCheckInHistory.usrRiskStat = 2;
   mainHistory4->nextMainCheckIn = NULL;
   mainHistory4->nextMainCheckIn = mainTop;
   mainTop = mainHistory4;

   VenueCheckInHistory* venueHistory4[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       venueHistory4[i] = new VenueCheckInHistory;
   }
   venueHistory4[0]->dateTime = "2022-04-10,17:47:52"; //Demonstration
   venueHistory4[0]->userID = "0194143449";
   venueHistory4[0]->usrRiskStat = 2;
   venueHistory4[0]->nextVenueCheckIn = NULL;
   venueHistory4[0]->nextVenueCheckIn = venueTop[0];
   venueTop[0] = venueHistory4[0];
}
/*------------------------------------------------------------------------------------------------------------ - */

// Function to pause terminal screen
void pauseScreen()
{
   cout << "Press any key to continue...\n";
   cin.clear();
   cin.ignore(100, '\n');
   cin.get();
}


//USER
/*------------------------------------------------------------------------------------------------------------ - */
User* registerUser = new User;
void registerAcc() {
   int registerOption = 0;

   while (registerOption != 1 && registerOption != 2)
   {
       cout << "\nEnter the method you would like to register with (1 or 2)" << endl
           << "1. Phone number \n2. Email \n"
           << "Select Option : ";
       cin >> registerOption;

       cout << "\n";
       if (registerOption == 1) {
           cout << "Phone Number: ";
           cin >> registerUser->id;
           while (registerUser->id == "")
           {
               cout << "\nPlease enter your phone number!";
               cout << "\nPhone Number: ";
               getline(cin, registerUser->id);
           }
       }
       else
           if (registerOption == 2) {
               cout << "Email: ";
               cin >> registerUser->id;
               while (registerUser->id == "")
               {
                   cout << "\nPlease enter your email!";
                   cout << "\nEmail: ";
                   getline(cin, registerUser->id);
               }
           }
           else {
               cout << "Please enter the correct option" << endl;
           }
   }

   cout << "\nFull name: ";
   cin.clear();
   cin.ignore(100, '\n');
   getline(cin, registerUser->name);
   while (registerUser->name == "")
   {
       cerr << "\nPlease enter your name!";
       cout << "\nFull name: ";
       getline(cin, registerUser->name);
   }

   cout << "\nNRIC/Passport Number: ";
   cin >> registerUser->identityNum;
   while (registerUser->identityNum == "")
   {
       cerr << "\nPlease enter your NRIC/Passport Number!";
       cout << "\nNRIC/Passport Number: ";
       getline(cin, registerUser->identityNum);
   }

   cout << "\nAge: ";
   cin >> registerUser->age;
   while (registerUser->age <= 0)
   {
       cerr << "\nPlease enter your age!";
       cout << "\nAge: ";
       cin >> registerUser->age;
   }

   cout << "\nCurrent Address: ";
   cin.ignore();
   getline(cin, registerUser->address);
   while (registerUser->address == "")
   {
       cout << "\nPlease enter your current address!";
       cout << "\nCurrent Address: ";
       getline(cin, registerUser->address);
   }

   cout << "\nGender(M/F): ";
   cin >> registerUser->gender;
   while (toupper(registerUser->gender) != 'M' && toupper(registerUser->gender) != 'F')
   {
       cerr << "\nPlease enter your gender!";
       cout << "\nGender(M/F): ";
       cin >> registerUser->gender;
   }

   cout << "\nEthnicity (1.Malay 2.Chinese 3.Indian 4.Others): ";
   cin >> registerUser->ethnic;
   while (registerUser->ethnic != 1 && registerUser->ethnic != 2 && registerUser->ethnic != 3 && registerUser->ethnic != 4)
   {
       cerr << "\nPlease enter your ethnicity!";
       cout << "\nEthnicity (1.Malay 2.Chinese 3.Indian 4.Others) : ";
       cin >> registerUser->ethnic;
   }

   cout << "\nPassword : ";
   cin >> registerUser->password;
   while (registerUser->password == "")
   {
       cerr << "\nPlease enter your password!";
       cout << "\nPassword : ";
       cin >> registerUser->password;
   }

   cout << "\nVaccination Status (1.Fully Vaccinated 2.Partially Vaccinated 3.Unvaccinated) : ";
   cin >> registerUser->vaccStatus;
   while (registerUser->vaccStatus != 1 && registerUser->vaccStatus != 2 && registerUser->vaccStatus != 3)
   {
       cerr << "\nPlease enter your vaccination status!";
       cout << "\nVaccination Status (1.Fully Vaccinated 2.Partially Vaccinated 3.Unvaccinated) : ";
       cin >> registerUser->vaccStatus;
   }

   // User's risk status is 'Low Risk' by default
   registerUser->riskStatus = 1;

   // Store Registered User to the User Linked List
   registerUser->nextUser = NULL;
   userTail->nextUser = registerUser;
   userTail = registerUser;

   cout << "\n\nYou have registered successfully!" << endl;
}

void logInAcc()
{
   string logInUsername = "empty", logInPassword = "empty";

   while (logInUsername != registerUser->id)
   {
       cout << "\nEnter phone number or email (Username): ";
       cin >> logInUsername;
       if (logInUsername != registerUser->id)
       {
           cerr << "Incorrect username!" << endl;
       }
   }

   while (logInPassword != registerUser->password)
   {
       cout << "\nEnter password: ";
       cin >> logInPassword;
       if (logInPassword != registerUser->password)
       {
           cerr << "Incorrect password!" << endl;
       }
   }
}

void editUserData()
{
   int editUser = 0, idOpt = 0;

   cout << " 1 - User ID\n"
       << " 2 - Current Address\n"
       << " 3 - Password\n"
       << " 4 - Previous Page\n"
       << "Select Option: ";
   cin >> editUser;

   if (editUser == 4) return;

   switch (editUser) {
   case 1: //Edit User ID
   {
       while (idOpt != 1 && idOpt != 2)
       {
           cout << "\nHow would you like to edit your ID? (1 or 2)" << endl
               << "1. Phone number \n2. Email \n"
               << "Select Option : ";
           cin >> idOpt;

           cout << "\n";
           if (idOpt == 1) {
               cout << "Edit Phone Number: ";
               cin >> registerUser->id;
               while (registerUser->id == "")
               {
                   cout << "\nPlease enter your phone number!";
                   cout << "\nEdit Phone Number: ";
                   getline(cin, registerUser->id);
               }
           }
           else
               if (idOpt == 2) {
                   cout << "Edit Email: ";
                   cin >> registerUser->id;
                   while (registerUser->id == "")
                   {
                       cout << "\nPlease enter your email!";
                       cout << "\nEdit Email: ";
                       getline(cin, registerUser->id);
                   }
               }
               else {
                   cout << "Please enter the correct option" << endl;
               }
       }
       break;
   }
   case 2: //Edit Address
   {
       cout << "\nEdit Current Address: ";
       cin.ignore();
       getline(cin, registerUser->address);
       while (registerUser->address == "")
       {
           cout << "\nPlease enter your current address!";
           cout << "\nEdit Current Address: ";
           getline(cin, registerUser->address);
       }
       break;
   }
   case 3: //Edit Password
   {
       cout << "\nEdit Password : ";
       cin >> registerUser->password;
       while (registerUser->password == "")
       {
           cerr << "\nPlease enter your password!";
           cout << "\nEdit Password : ";
           cin >> registerUser->password;
       }
       break;
   }
   default:
       break;
   }
   userTail = registerUser;
}
/*------------------------------------------------------------------------------------------------------------ - */


//DEPENDENT
/*------------------------------------------------------------------------------------------------------------ - */
void addDependents()
{
   int depOrder = 0;
   struct Dependent dep;

   // Check if user have already registered 2 dependent (full)
   if (registerUser->dep[1].fullName != "")
   {
       cout << "\Sorry. You can only add a maximum of 2 dependents.\n" << endl;
       return;
   }

   // Check if user have already registered 1 dependent
   if (registerUser->dep[0].fullName != "")
   {
       depOrder = 1;
   }

   cout << "\n- Enter details for dependent " << depOrder + 1 << " -" << endl;

   cout << "\nFull name : ";
   cin.ignore();
   getline(cin, dep.fullName);
   while (dep.fullName == "")
   {
       cout << "\nPlease enter your name!";
       cout << "\nFull name : ";
       getline(cin, dep.fullName);
   }

   cout << "\nRelation " << endl;
   cout << "1.Spouse\n2.Child\n3.Siblings\n4.Parents/Parent-in-law\n5.Grandparents\n6.Guardians\n7.Others" << endl;
   cout << "Option : ";
   cin >> dep.relation;
   while (dep.relation == 0)
   {
       cout << "\nPlease enter your relation!";
       cout << "\nRelation ";
       cout << "1.Spouse 2.Child 3.Siblings 4.Parents/Parent-in-law 5.Grandparents 6.Guardians 7.Others" << endl;
       cout << "Option : ";
       cin >> dep.relation;
   }

   cout << "\nNRIC/Passport Number : ";
   cin >> dep.IC;
   while (dep.IC == "")
   {
       cout << "\nPlease enter your NRIC/Passport Number!";
       cout << "\nNRIC/Passport Number : ";
       cin >> dep.IC;
   }

   cout << "\nAge : ";
   cin >> dep.age;
   while (dep.age <= 0)
   {
       cout << "\nPlease enter your age!";
       cout << "\nAge : ";
       cin >> dep.age;
   }

   cout << "\nGender(M/F) : ";
   cin >> dep.gender;
   while (toupper(dep.gender) != 'M' && toupper(dep.gender) != 'F')
   {
       cout << "\nPlease enter your gender!";
       cout << "\nGender(M/F) : ";
       cin >> dep.gender;
   }

   cout << "\nCurrent Address : ";
   cin.ignore(100, '\n');
   getline(cin, dep.currentAddress);
   while (dep.currentAddress == "")
   {
       cin.ignore(100, '\n');
       cout << "\nPlease enter your current address!";
       cout << "\nCurrent Address : ";
       getline(cin, dep.currentAddress);
   }

   // Store Dependent data
   registerUser->dep[depOrder].fullName = dep.fullName;
   registerUser->dep[depOrder].relation = dep.relation;
   registerUser->dep[depOrder].IC = dep.IC;
   registerUser->dep[depOrder].age = dep.age;
   registerUser->dep[depOrder].gender = dep.gender;
   registerUser->dep[depOrder].currentAddress = dep.currentAddress;
   registerUser->dep[depOrder].riskStatus = 1;
   
   cout << "\nYou have added the dependent successfully!" << endl;
}

void editDependents()
{
   int depOpt, editDep;

   if (registerUser->dep[0].fullName == "")
   {
       cout << "\nYou don't have any registered dependents.\n\n";
       return;
   }

   cout << " 1 - " << registerUser->dep[0].fullName << endl;
   if (registerUser->dep[1].fullName != "")
       cout << " 2 - " << registerUser->dep[1].fullName << endl;
   cout << " 3 - Previous Page" << endl;
   cout << "Select Option : ";
   cin >> depOpt;
   if (depOpt == 3) return;

   while (depOpt != 1 && depOpt != 2) {
       cout << "\nPlease enter the correct dependent number!" << endl;
       cout << "\nSelect Option : ";
       cin >> depOpt;
   }
   depOpt--;

   cout << "\033[2J\033[1;1H";
   cout << "- Edit " << registerUser->dep[depOpt].fullName << "\'s Particular - \n"
       << " 1 - Current Address\n"
       << " 2 - Return to Manage Dependent\n"
       << "Select Option: ";
   cin >> editDep;

   if (editDep == 2)
       return;
   else if (editDep == 1)
   {
       cout << "\nEdit Current Address : ";
       cin.ignore(100, '\n');
       getline(cin, registerUser->dep[depOpt].currentAddress);
       while (registerUser->dep[depOpt].currentAddress == "")
       {
           cin.ignore(100, '\n');
           cout << "\nPlease enter your current address!";
           cout << "\nEdit Current Address : ";
           getline(cin, registerUser->dep[depOpt].currentAddress);
       }
   }
   cout << "\nDependent \"" << registerUser->dep[depOpt].fullName << "\" data has been updated.\n" << endl;
}

void manageDependents()
{
   int manageOpt = 0;

   do
   {
       cout << "\033[2J\033[1;1H";
       cout << "[Manage Dependents]\n"
           << " 1 - Add Dependents\n"
           << " 2 - Edit Dependents\n"
           << " 3 - Previous Page\n"
           << "Select Option: ";
       cin >> manageOpt;

       switch (manageOpt)
       {
       case 1: //Add Dependents
       {
           cout << "\033[2J\033[1;1H";
           cout << "[Add Dependents]\n";
           addDependents();
           pauseScreen();
           break;
       }
       case 2: //Edit Dependents
       {
           cout << "\033[2J\033[1;1H";
           cout << "[Select a Dependent to Edit]\n";
           editDependents();
           pauseScreen();
           break;
       }
       default:
           break;
       }
   } while (manageOpt != 3);
}
/*------------------------------------------------------------------------------------------------------------ - */

// Function to extract system date & time
string systemDate()
{
   time_t rawtime;
   struct tm* timeinfo;
   char buffer[80];

   time(&rawtime);
   timeinfo = localtime(&rawtime);

   strftime(buffer, sizeof(buffer), "%Y-%m-%d,%H:%M:%S", timeinfo);
   string str(buffer);

   return str;
}

// Function to convert date & time that has been saved in strong format to time stamp format
time_t StringToTimestamp(const string& timeString)
{
   tm tm{};
   stringstream ss(timeString);
   ss >> get_time(&tm, "%Y-%m-%d,%H:%M:%S");

   time_t timestamp = mktime(&tm);

   return  mktime(&tm);
}


// IDENTIFY ID's and return value in string
/*------------------------------------------------------------------------------------------------------------ - */
string identifyVenue(int venueId)
{
   string venueName = "";
   switch (venueId)
   {
   case 0:
       venueName = "Sunway Pyramid";
       break;
   case 1:
       venueName = "UoWMKDU";
       break;
   case 2:
       venueName = "Family Mart";
       break;
   }
   return venueName;
}

string identifyRisk(int riskId)
{
   string riskStat = "";
   switch (riskId)
   {
   case 1:
       riskStat = "Low Risk";
       break;
   case 2:
       riskStat = "Infected";
       break;
   case 3:
       riskStat = "Close Contact";
       break;
   }
   return riskStat;
}

string identifyVaccStat(int vaccStat)
{
   string vaccStatus;
   switch (vaccStat)
   {
   case 1:
       vaccStatus = "Fully Vaccinated";
       break;
   case 2:
       vaccStatus = "Partially Vaccinated";
       break;
   case 3:
       vaccStatus = "Unvaccinated";
       break;
   }
   return vaccStatus;
}

string identifyGender(int genderId)
{
   string gender = "";
   switch (toupper(genderId))
   {
   case 'M':
       gender = "Male";
       break;
   case 'F':
       gender = "Female";
       break;
   }
   return gender;
}

string identifyRelation(int relationId)
{
   string relation = "";
   switch (relationId)
   {
   case 1:
       relation = "Spouse";
       break;
   case 2:
       relation = "Child";
       break;

   case 3:
       relation = "Siblings";
       break;

   case 4:
       relation = "Parents/Parent-in-law";
       break;

   case 5:
       relation = "Grandparents";
       break;

   case 6:
       relation = "Guardians";
       break;

   case 7:
       relation = "Others";
       break;
   }
   return relation;
}
/*------------------------------------------------------------------------------------------------------------ - */

void checkIn() {
   int checkInOpt = 0;
   char dependentTracing = ' ';
   bool depTracing = false;

   UserCheckInHistory* userCheckIn = new UserCheckInHistory;
   MainCheckInHistory* mainCheckIn = new MainCheckInHistory;
   VenueCheckInHistory* venueCheckIn[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       venueCheckIn[i] = new VenueCheckInHistory;
   }

   cout << "\nPlease choose your Check-in location" << endl
       << " 1 - Sunway Pyramid" << endl
       << " 2 - UoWMKDU" << endl
       << " 3 - Family Mart" << endl
       << "Select Option : ";
   cin >> checkInOpt;
   checkInOpt--;

   // Prompt to ask user if his dependent is together while checking in
   for (int i = 0; i < 2; i++)
   {
       if (registerUser->dep[i].fullName != "")
       {
           cin.clear();
           cin.ignore();
           cout << "\nIs " << registerUser->dep[i].fullName << " with you? (Y/N): ";
           cin >> dependentTracing;

           depTracing = (toupper(dependentTracing) == 'Y') ? true : false;

           venueCheckIn[checkInOpt]->dependentTrace[i] = depTracing;
           venueCheckIn[checkInOpt]->depRiskStat[i] = registerUser->dep[i].riskStatus;

           userCheckIn->userCheckInHistory.dependentTrace[i] = venueCheckIn[checkInOpt]->dependentTrace[i];
           userCheckIn->userCheckInHistory.depRiskStat[i] = venueCheckIn[checkInOpt]->depRiskStat[i];

           mainCheckIn->mainCheckInHistory.userCheckInHistory.dependentTrace[i] = venueCheckIn[checkInOpt]->dependentTrace[i];
           mainCheckIn->mainCheckInHistory.userCheckInHistory.depRiskStat[i] = venueCheckIn[checkInOpt]->depRiskStat[i];
       }
       else
           break;
       cout << "\n";
   }

   //STORING CHECK-IN HISTORIES IN A STACK LINKED LIST BELOW
   //Store Venue Check In History
   venueCheckIn[checkInOpt]->dateTime = systemDate();
   venueCheckIn[checkInOpt]->userID = registerUser->id;
   venueCheckIn[checkInOpt]->usrRiskStat = registerUser->riskStatus;

   venueCheckIn[checkInOpt]->nextVenueCheckIn = NULL;
   venueCheckIn[checkInOpt]->nextVenueCheckIn = venueTop[checkInOpt];
   venueTop[checkInOpt] = venueCheckIn[checkInOpt];


   //Store User Check In History
   userCheckIn->userCheckInHistory.dateTime = systemDate();
   userCheckIn->userCheckInHistory.userID = registerUser->id;
   userCheckIn->venueID = checkInOpt;
   userCheckIn->userCheckInHistory.usrRiskStat = registerUser->riskStatus;

   userCheckIn->nextUserCheckIn = NULL;
   userCheckIn->nextUserCheckIn = userTop;
   userTop = userCheckIn;


   //Store Main Check In History
   mainCheckIn->mainCheckInHistory.userCheckInHistory.dateTime = systemDate();
   mainCheckIn->mainCheckInHistory.userCheckInHistory.userID = registerUser->id;
   mainCheckIn->mainCheckInHistory.venueID = checkInOpt;
   mainCheckIn->mainCheckInHistory.userCheckInHistory.usrRiskStat = registerUser->riskStatus;

   mainCheckIn->nextMainCheckIn = NULL;
   mainCheckIn->nextMainCheckIn = mainTop;
   mainTop = mainCheckIn;
}

// Add Close Contact User to each Venue
void addCloseCon(string closeConName, int venueID) {
   CloseContact* newCloseCon[VENUESIZE];
   for (int i = 0; i < VENUESIZE; i++)
   {
       newCloseCon[i] = new CloseContact;
   }

   // Assign values to 'newClosCon'
   newCloseCon[venueID]->name = closeConName;
   newCloseCon[venueID]->nextCloseCon = NULL;

   // Add name to close contact list
   if (closeConHead[venueID] == NULL) {
       closeConHead[venueID] = newCloseCon[venueID];
   }
   else
   {
       // Check if the added names are duplicated
       CloseContact* closeConNavi = closeConHead[venueID];
       if (closeConNavi->name == closeConName)
           return;
       while (closeConNavi->nextCloseCon != NULL) {
           if (closeConNavi->name == closeConName)
               return;
           closeConNavi = closeConNavi->nextCloseCon;
       }
       if (closeConNavi->name == closeConName)
           return;
       closeConNavi->nextCloseCon = newCloseCon[venueID];
   }
}

void contactTracing()
{
   string covidUser = "", covidDateTime = "";
   int covidVenue = 0;
   double timeDiff = 0.0;

   User* usrNavi = userHead;
   UserCheckInHistory* userNavi = userTop;
   MainCheckInHistory* mainNavi = mainTop;

   // Search thgough the main check in history and find out who is infected
   // Then use another while loop to locate the user in user linked list by user ID
   // when we locate the user, we compare the risk status
   // if risk status is 2, we found the infected person
   // Thenm extract the infected person's userID, check-in venueID, check-in date & time
   while (mainNavi != NULL)
   {
       usrNavi = userHead;
       while (usrNavi != NULL)
       {
           if (usrNavi->id == mainNavi->mainCheckInHistory.userCheckInHistory.userID && usrNavi->riskStatus == 2)
           {
               // What if there is 2 and above ppl infected in a real mysejaterah?
               covidUser = usrNavi->id;
               covidVenue = mainNavi->mainCheckInHistory.venueID;
               covidDateTime = mainNavi->mainCheckInHistory.userCheckInHistory.dateTime;
               break;
           }
           usrNavi = usrNavi->nextUser;
       }
       mainNavi = mainNavi->nextMainCheckIn;
   }

   VenueCheckInHistory* venNavi = venueTop[covidVenue];

   //Within 24 hour is considered as close contact
   string beg = covidDateTime;
   time_t begTm = StringToTimestamp(beg);

   //Once we've located infected person date & time (infected node) in the venue check in history
   //Then we calculate the time difference of each check in history in venue check-in history
   //Take note that will only search through the venue check in history untill the location of the 'infected node'
   //1440 min = 24 hours
   //If within 24 hours, we change the affected user's risk status to 'close contact'
   if (covidUser != "")
   {
       venNavi = venueTop[covidVenue];
       //Only search up to the covid time, don't touch the older data
       while (venNavi->dateTime != covidDateTime)
       {
           string end = venNavi->dateTime;
           time_t endTm = StringToTimestamp(end);

           // Calculate time difference
           // If within 24 hours, update user risk status to 'close contact'
           timeDiff = difftime(endTm, begTm) / 60;
           if (timeDiff <= 1440.00 && timeDiff > 0)
           {
               // Update Venue Check-in History
               venNavi->usrRiskStat = 3;
               for (int i = 0; i < 2; i++)
               {
                   if (venNavi->dependentTrace[i] == true)
                       venNavi->depRiskStat[i] = 3;
               }

               // Update User Check-in History
               userNavi = userTop;
               while (userNavi != NULL)
               {
                   if (userNavi->userCheckInHistory.dateTime == venNavi->dateTime)
                   {
                       userNavi->userCheckInHistory.usrRiskStat = 3;
                       for (int j = 0; j < 2; j++)
                       {
                           if (userNavi->userCheckInHistory.dependentTrace[j] == true)
                               userNavi->userCheckInHistory.depRiskStat[j] = 3;
                       }
                       break;
                   }
                   userNavi = userNavi->nextUserCheckIn;
               }

               // Update Main Check-in History
               mainNavi = mainTop;
               while (mainNavi != NULL)
               {
                   if (mainNavi->mainCheckInHistory.userCheckInHistory.dateTime == venNavi->dateTime)
                   {
                       mainNavi->mainCheckInHistory.userCheckInHistory.usrRiskStat = 3;
                       for (int j = 0; j < 2; j++)
                       {
                           if (mainNavi->mainCheckInHistory.userCheckInHistory.dependentTrace[j] == true)
                               mainNavi->mainCheckInHistory.userCheckInHistory.depRiskStat[j] = 3;
                       }
                       break;
                   }
                   mainNavi = mainNavi->nextMainCheckIn;
               }

               // Update User & Dependent Risk Status
               usrNavi = userHead;
               while (usrNavi != NULL)
               {
                   if (venNavi->userID == usrNavi->id)
                   {
                       usrNavi->riskStatus = 3;
                       addCloseCon(usrNavi->name, covidVenue); // Add to close contact list
                       for (int j = 0; j < 2; j++)
                       {
                           if (venNavi->dependentTrace[j] == true) {
                               addCloseCon(usrNavi->dep[j].fullName, covidVenue);
                               usrNavi->dep[j].riskStatus = 3;
                           }
                       }
                       break;
                   }
                   usrNavi = usrNavi->nextUser;
               }
               cout << "\n\n";
           }
           venNavi = venNavi->nextVenueCheckIn;
       }
   }
}


// DISPLAY VALUE
/*------------------------------------------------------------------------------------------------------------ - */
void displayMainCheckInHistory()
{
   User* userNavi = userHead;
   MainCheckInHistory* naviMainHsty = mainTop;

   cout << "\n";
   if (naviMainHsty == NULL)
   {
       cout << "History is Empty." << endl;
       cout << " " << endl;
       return;
   }

   while (naviMainHsty != NULL)
   {
       cout << "User ID: " << naviMainHsty->mainCheckInHistory.userCheckInHistory.userID << endl;
       cout << "Risk Status: " << identifyRisk(naviMainHsty->mainCheckInHistory.userCheckInHistory.usrRiskStat) << endl;
       cout << "Vaccination Status: ";
       userNavi = userHead;
       while (userNavi != NULL)
       {
           if (userNavi->id == naviMainHsty->mainCheckInHistory.userCheckInHistory.userID)
           {
               cout << identifyVaccStat(userNavi->vaccStatus) << endl;
               break;
           }
           userNavi = userNavi->nextUser;
       }
       cout << "Venue : " << identifyVenue(naviMainHsty->mainCheckInHistory.venueID) << endl;
       cout << "Check In Date & Time: " << naviMainHsty->mainCheckInHistory.userCheckInHistory.dateTime << endl;
       naviMainHsty = naviMainHsty->nextMainCheckIn;
       cout << "\n";
   }
   cout << "\n\n";
}

void displayCheckInHistory() {
   UserCheckInHistory* naviHistory = new UserCheckInHistory;
   User* userNavigate = userHead;
   int viewDetailOpt = 0;

   naviHistory = userTop;
   cout << "\n";
   if (naviHistory == NULL)
   {
       cout << "History is Empty." << endl;
       cout << " " << endl;
       return;
   }

   for (int i = 1; naviHistory != NULL; i++)
   {
       cout << "Check-In ID: " << i << endl;
       cout << "Venue: " << identifyVenue(naviHistory->venueID) << endl;
       cout << "Check In Date & Time: " << naviHistory->userCheckInHistory.dateTime << endl;
       naviHistory = naviHistory->nextUserCheckIn;
       cout << "\n";
   }

   cout << "Select Check-in ID to view details or (-1) to exit.\n"
       << "Option: ";
   cin >> viewDetailOpt;

   if (viewDetailOpt == -1) return;

   // Display check-in details
   // Search through user linked list to display selected history 
   naviHistory = userTop;
   for (int i = 1; i < viewDetailOpt; i++)
   {
       naviHistory = naviHistory->nextUserCheckIn;
   }

   cout << "\033[2J\033[1;1H";
   cout << "[Check-in Information]\n\n";
   cout << "Venue: " << identifyVenue(naviHistory->venueID) << endl;
   cout << "Name : ";
   while (userNavigate != NULL)
   {
       if (userNavigate->id == naviHistory->userCheckInHistory.userID)
       {
           cout << userNavigate->name;
           cout << " (" << identifyRisk(naviHistory->userCheckInHistory.usrRiskStat) << ")" << endl;
           break;
       }
       userNavigate = userNavigate->nextUser;
   }


   // Display dependent name if he/she checked in with user at selected check in history
   if (naviHistory->userCheckInHistory.dependentTrace[0] == true || naviHistory->userCheckInHistory.dependentTrace[1] == true)
   {
       cout << "Dependent: ";
       if (naviHistory->userCheckInHistory.dependentTrace[0] == true)
       {
           cout << registerUser->dep[0].fullName << " (" << identifyRisk(naviHistory->userCheckInHistory.depRiskStat[0]) << ")";
           if (naviHistory->userCheckInHistory.dependentTrace[1] == true)
               cout << ", " << registerUser->dep[1].fullName << " (" << identifyRisk(naviHistory->userCheckInHistory.depRiskStat[1]) << ")";
       }
       else
           if (naviHistory->userCheckInHistory.dependentTrace[1] == true)
               cout << registerUser->dep[1].fullName << " (" << identifyRisk(naviHistory->userCheckInHistory.depRiskStat[1]) << ")";

       cout << endl;
   }
   cout << "Check In Date & Time: " << naviHistory->userCheckInHistory.dateTime << endl;
   cout << "\n";
}

void displayDependent() {

   int dependent;

   if (registerUser->dep[0].fullName == "")
   {
       cout << "\nYou don't have any registered dependents.\n\n";
       return;
   }

   cout << "\nWhich dependent's details would you like to see?" << endl;
   cout << " 1 - " << registerUser->dep[0].fullName << endl;
   if (registerUser->dep[1].fullName != "")
       cout << " 2 - " << registerUser->dep[1].fullName << endl;
   cout << "Select Option : ";
   cin >> dependent;
   while (dependent != 1 && dependent != 2) {
       cout << "\nPlease enter the correct dependent number! " << endl;
       cout << "\nOption : ";
       cin >> dependent;
   }
   dependent--;

   cout << "\033[2J\033[1;1H";
   cout << "- Details of Dependent " << dependent + 1 << " -" << endl;
   cout << "\nFull Name  : " << registerUser->dep[dependent].fullName << endl;
   cout << "Risk Status: " << identifyRisk(registerUser->dep[dependent].riskStatus) << endl;
   cout << "Relation   : " << identifyRelation(registerUser->dep[dependent].relation) << endl;
   cout << "NRIC/Passport Number: " << registerUser->dep[dependent].IC << endl;
   cout << "Age : " << registerUser->dep[dependent].age << endl;
   cout << "Gender : " << identifyGender(registerUser->dep[dependent].gender) << endl;
   cout << "Current Address : " << registerUser->dep[dependent].currentAddress << endl;

   cout << "\n";
}

void displayCloseCon()
{
	VenueCheckInHistory* venueHsty[VENUESIZE];
	CloseContact* closeCon[VENUESIZE];
	for (int i = 0; i < VENUESIZE; i++)
	{
		venueHsty[i] = new VenueCheckInHistory;
		closeCon[i] = closeConHead[i];
	}

   for (int i = 0; i < VENUESIZE; i++) {
       cout << "[" << identifyVenue(i) << " Close Contact]" << endl;

       if (closeCon[i] == NULL)
           cout << "Empty." << endl;
       else {
           for (int j = 1; closeCon[i] != NULL; j++) {
               cout << " " << j << ". " << closeCon[i]->name << endl;
               closeCon[i] = closeCon[i]->nextCloseCon;
           }
       }
       cout << "\n\n";
   }
}
/*------------------------------------------------------------------------------------------------------------ - */

int main()
{
   hardCodeCheckInHistory();
   hardCodeUser();

   int menuOption = 0, logInAction = 0;
   bool logInDetails;

   do {
       cout << "\033[2J\033[1;1H"; // Clear Terminal Screen
       cout << "[Vibes Cracked mySejahtera]\n";
       cout << " 1 - Register\n"
           << " 2 - Log In\n"
           << " 3 - Exit Program\n"
           << "Select Option : ";
       cin >> menuOption;

       switch (menuOption) {
       case 1: // Register
       {
           cout << "\033[2J\033[1;1H";
           cout << "[Register New Account]\n";
           registerAcc();
           pauseScreen();
           break;
       }
       case 2: // Log In
       {
           cout << "\033[2J\033[1;1H";
           cout << "[Log In to Existing Account]\n";
           logInAcc();

           do
           {
               //We try to make it similar as the actual mysejahtera app where the risk status will update each 
               //time the user refreshes. But in our case, we refresh it everytime we go back to the main menu.
               contactTracing();

               cout << "\033[2J\033[1;1H";
               cout << "Welcome Back, " << registerUser->name << "! \n\n";

               cout << "Risk Status: " << identifyRisk(registerUser->riskStatus) << "\n\n";

               cout << " 1 - Check In\n"
                   << " 2 - View Check In History\n"
                   << " 3 - Edit User Particular\n"
                   << " 4 - Manage Dependents\n"
                   << " 5 - View Dependents\n"
                   << " 6 - View Close Contact (for demonstration)\n"
                   << " 7 - View Main Check In History (for demonstration)\n"
                   << " 8 - Log Out\n"
                   << "Select Option : ";
               cin >> logInAction;

               switch (logInAction)
               {
               case 1: //Check In
               {
                   cout << "\033[2J\033[1;1H";
                   cout << "[Check In]\n";
                   checkIn();
                   pauseScreen();
                   break;
               }
               case 2: //View Check In History
               {
                   cout << "\033[2J\033[1;1H";
                   cout << "[Check In History]\n";
                   displayCheckInHistory();
                   pauseScreen();
                   break;
               }
               case 3:
               {
                   cout << "\033[2J\033[1;1H";
                   cout << "[Edit User Particular]\n";
                   editUserData();
                   pauseScreen();
                   break;
               }
               case 4: //Manage dependents
               {
                   manageDependents();
                   pauseScreen();
                   break;
               }
               case 5: //View Dependents
               {
                   cout << "\033[2J\033[1;1H";
                   cout << "[View Dependents]\n";
                   displayDependent();
                   pauseScreen();
                   break;
               }
               case 6: //View Close Contact
               {
                   cout << "\033[2J\033[1;1H";
                   displayCloseCon();
                   pauseScreen();
                   break;
               }
               case 7: //View Main Check-in History
               {
                   cout << "\033[2J\033[1;1H";
                   cout << "[Main Check In History]\n";
                   displayMainCheckInHistory();
                   pauseScreen();
                   break;
               }
               case 8: //Log Out
               {
                   cout << "\033[2J\033[1;1H";
                   cout << "Log Out Successfull :D\n\n";
                   pauseScreen();
                   break;
               }
               }
           } while (logInAction != 8);
           break;
       }
       case 3: // Exit Program
       {
           cout << "\033[2J\033[1;1H";
           cout << "Program Exiting...Thank You for Using Vibes Cracked mySejahtera\n\n";
           pauseScreen();
           break;
       }
       }
   } while (menuOption != 3);
}



//References for calculating time difference: 
//https://stackoverflow.com/questions/69582117/calculating-difference-between-two-date-times-in-c
//https://gist.github.com/dmthuc/a5900cce9fcf03d76c25ce3fb86a9ac3
//https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm

//To be improved:
// If 2 or more person is infected, should we implement another linked list for infected person?
// Revert user's risk status (close contact) after a period of time (implement a close contact time, save in database)
// Should we add dependent to user linled list?
// What if dependent is infected?
// Calculate total infected person & close contact