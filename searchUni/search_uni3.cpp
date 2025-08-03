#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <chrono>
using namespace std;
using namespace std::chrono;

struct UniNode {
	string UniID, Insitution, LocationCode, Location, addon;
	double ArScore, ErScore, FsrScore, CpfScore, IfrScore, IsrScore, IrnScore, GerScore, ScoreScaled;
	int Rank, ArRank, ErRank, FsrRank, CpfRank, IfrRank, IsrRank, IrnRank, GerRank;
	UniNode* NextAdd;
} *head;

UniNode* createNewUniNode(int Rank, string Insitution, string LocationCode, string Location, double ArScore, int ArRank,
	double ErScore, int ErRank, double FsrScore, int FsrRank, double CpfScore, int CpfRank, double IfrScore, int IfrRank,
	double IsrScore, int IsrRank, double IrnScore, int IrnRank, double GerScore, int GerRank, double ScoreScaled) {

	UniNode* newUniNode = new UniNode;
	string UniID = to_string(Rank);
	UniID = string(4 - UniID.length(), '0') + UniID;
	newUniNode->UniID = "UNI" + UniID;
	newUniNode->Rank = Rank;
	newUniNode->Insitution = Insitution;
	newUniNode->LocationCode = LocationCode;
	newUniNode->Location = Location;
	newUniNode->ArScore = ArScore;
	newUniNode->ArRank = ArRank;
	newUniNode->ErScore = ErScore;
	newUniNode->ErRank = ErRank;
	newUniNode->FsrScore = FsrScore;
	newUniNode->FsrRank = FsrRank;
	newUniNode->CpfScore = CpfScore;
	newUniNode->CpfRank = CpfRank;
	newUniNode->IfrScore = IfrScore;
	newUniNode->IfrRank = IfrRank;
	newUniNode->IsrScore = IsrScore;
	newUniNode->IsrRank = IsrRank;
	newUniNode->IrnScore = IrnScore;
	newUniNode->IrnRank = IrnRank;
	newUniNode->GerScore = GerScore;
	newUniNode->GerRank = GerRank;
	newUniNode->ScoreScaled = ScoreScaled;
	newUniNode->NextAdd = NULL;
	return newUniNode;
}

//quick sort algorithms - 0
void swap(UniNode& a, UniNode& b) {
	UniNode temp = a;
	a = b;
	b = temp;
}

int partitionByInst(UniNode* uniArr, int left, int right) {
	string pivot = uniArr[right].Insitution;
	int i = left - 1;
	for (int j = left; j <= right - 1; j++) {
		if (uniArr[j].Insitution <= pivot) {
			i++;
			swap(uniArr[i], uniArr[j]);
		}
	}
	swap(uniArr[i + 1], uniArr[right]);
	return i + 1;
}
void quickSortInst(UniNode* uniArr, int left, int right) {
	if (left < right) {
		int pi = partitionByInst(uniArr, left, right);
		quickSortInst(uniArr, left, pi - 1);
		quickSortInst(uniArr, pi + 1, right);
	}
}

int partitionByLoc(UniNode* uniArr, int left, int right) {
	string pivot = uniArr[right].Location;
	int i = left - 1;
	for (int j = left; j <= right - 1; j++) {
		if (uniArr[j].Location <= pivot) {
			i++;
			swap(uniArr[i], uniArr[j]);
		}
	}
	swap(uniArr[i + 1], uniArr[right]);
	return i + 1;
}
void quickSortLoc(UniNode* uniArr, int left, int right) {
	if (left < right) {
		int pi = partitionByLoc(uniArr, left, right);
		quickSortLoc(uniArr, left, pi - 1);
		quickSortLoc(uniArr, pi + 1, right);
	}
}
//quick sort algorithms - 1

void binarySearchInst(UniNode* uniArr, int size, const string& searchTerm) {
	auto start = high_resolution_clock::now();
	int left = 0;
	int right = size - 1;
	bool found = false;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (uniArr[mid].Insitution == searchTerm) {
			cout << "Rank: " << uniArr[mid].Rank << endl;
			cout << "Inistitution: " << uniArr[mid].Insitution << endl;
			cout << "Location Code: " << uniArr[mid].LocationCode << endl;
			cout << "Location: " << uniArr[mid].Location << endl;
			cout << "Academic Reputation Score: " << uniArr[mid].ArScore << endl;
			cout << "Academic Reputation Rank: " << uniArr[mid].ArRank << endl;
			cout << "Employer Reputation Score: " << uniArr[mid].ErScore << endl;
			cout << "Employer Reputation Rank: " << uniArr[mid].ErRank << endl;
			cout << "Faculty/Student Ratio Score: " << uniArr[mid].FsrScore << endl;
			cout << "Faculty/Student Ratio Rank: " << uniArr[mid].FsrRank << endl;
			cout << "Citations per Faculty Score: " << uniArr[mid].CpfScore << endl;
			cout << "Citations per Faculty Rank: " << uniArr[mid].CpfRank << endl;
			cout << "International Faculty Ratio Score: " << uniArr[mid].IfrScore << endl;
			cout << "International Faculty Ratio Rank: " << uniArr[mid].IfrRank << endl;
			cout << "International Student Ratio Score: " << uniArr[mid].IsrScore << endl;
			cout << "International Student Ratio Rank: " << uniArr[mid].IsrRank << endl;
			cout << "International Research Network Score: " << uniArr[mid].IrnScore << endl;
			cout << "International Research Network Rank: " << uniArr[mid].IrnRank << endl;
			cout << "Employment Outcome Score: " << uniArr[mid].GerScore << endl;
			cout << "Employment Outcome Rank: " << uniArr[mid].GerRank << endl;
			cout << "Score Scaled: " << uniArr[mid].ScoreScaled << endl;
			found = true;
			break;
		}
		else if (uniArr[mid].Insitution < searchTerm) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	if (!found) {
		cout << "Institution Not Found!" << endl;
	}
	cout << endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << endl << "Time taken by Binary search algorithm: " << duration.count() << " microseconds" << endl;
}

int binarySearchLoc(UniNode* uniArr, int size, const string& searchTerm) {
	int left = 0;
	int right = size - 1;
	int result = -1;
	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (uniArr[mid].Location < searchTerm) {
			left = mid + 1;
		}
		else if (uniArr[mid].Location > searchTerm) {
			right = mid - 1;
		}
		else {
			result = mid;
			right = mid - 1;
		}
	}
	return result;
}

void displayInfoByLoc(UniNode* uniArr, int size, const string& searchTerm) {
	auto start = high_resolution_clock::now();
	int startInd = binarySearchLoc(uniArr, size, searchTerm);
	if (startInd == -1) {
		cout << "No Institutions Found at this Location" << endl;
		return;
	}
	int endInd = size - 1;
	for (int i = startInd; i <= endInd; i++) {
		if (uniArr[i].Location != searchTerm) {
			break;
		}
		cout << "Rank: " << uniArr[i].Rank << endl;
		cout << "Inistitution: " << uniArr[i].Insitution << endl;
		cout << "Location Code: " << uniArr[i].LocationCode << endl;
		cout << "Location: " << uniArr[i].Location << endl;
		cout << "Academic Reputation Score: " << uniArr[i].ArScore << endl;
		cout << "Academic Reputation Rank: " << uniArr[i].ArRank << endl;
		cout << "Employer Reputation Score: " << uniArr[i].ErScore << endl;
		cout << "Employer Reputation Rank: " << uniArr[i].ErRank << endl;
		cout << "Faculty/Student Ratio Score: " << uniArr[i].FsrScore << endl;
		cout << "Faculty/Student Ratio Rank: " << uniArr[i].FsrRank << endl;
		cout << "Citations per Faculty Score: " << uniArr[i].CpfScore << endl;
		cout << "Citations per Faculty Rank: " << uniArr[i].CpfRank << endl;
		cout << "International Faculty Ratio Score: " << uniArr[i].IfrScore << endl;
		cout << "International Faculty Ratio Rank: " << uniArr[i].IfrRank << endl;
		cout << "International Student Ratio Score: " << uniArr[i].IsrScore << endl;
		cout << "International Student Ratio Rank: " << uniArr[i].IsrRank << endl;
		cout << "International Research Network Score: " << uniArr[i].IrnScore << endl;
		cout << "International Research Network Rank: " << uniArr[i].IrnRank << endl;
		cout << "Employment Outcome Score: " << uniArr[i].GerScore << endl;
		cout << "Employment Outcome Rank: " << uniArr[i].GerRank << endl;
		cout << "Score Scaled: " << uniArr[i].ScoreScaled << endl;
		cout << "-------------------------------------------------------------------" << endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << endl << "Time taken by Binary search algorithm: " << duration.count() << " microseconds" << endl;
}

void linearSearchInst(UniNode* uniArr, int size, const string& searchTerm) {
	auto start = high_resolution_clock::now();
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (uniArr[i].Insitution == searchTerm) {
			cout << "Rank: " << uniArr[i].Rank << endl;
			cout << "Inistitution: " << uniArr[i].Insitution << endl;
			cout << "Location Code: " << uniArr[i].LocationCode << endl;
			cout << "Location: " << uniArr[i].Location << endl;
			cout << "Academic Reputation Score: " << uniArr[i].ArScore << endl;
			cout << "Academic Reputation Rank: " << uniArr[i].ArRank << endl;
			cout << "Employer Reputation Score: " << uniArr[i].ErScore << endl;
			cout << "Employer Reputation Rank: " << uniArr[i].ErRank << endl;
			cout << "Faculty/Student Ratio Score: " << uniArr[i].FsrScore << endl;
			cout << "Faculty/Student Ratio Rank: " << uniArr[i].FsrRank << endl;
			cout << "Citations per Faculty Score: " << uniArr[i].CpfScore << endl;
			cout << "Citations per Faculty Rank: " << uniArr[i].CpfRank << endl;
			cout << "International Faculty Ratio Score: " << uniArr[i].IfrScore << endl;
			cout << "International Faculty Ratio Rank: " << uniArr[i].IfrRank << endl;
			cout << "International Student Ratio Score: " << uniArr[i].IsrScore << endl;
			cout << "International Student Ratio Rank: " << uniArr[i].IsrRank << endl;
			cout << "International Research Network Score: " << uniArr[i].IrnScore << endl;
			cout << "International Research Network Rank: " << uniArr[i].IrnRank << endl;
			cout << "Employment Outcome Score: " << uniArr[i].GerScore << endl;
			cout << "Employment Outcome Rank: " << uniArr[i].GerRank << endl;
			cout << "Score Scaled: " << uniArr[i].ScoreScaled << endl;

			found = true;
		}
	}
	if (!found) {
		cout << "Institution Not Found!" << endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << endl << "Time taken by Linear Search Algorithm: " << duration.count() << " microseconds" << endl;
}

void linearSearchLoc(UniNode* uniArr, int size, const string& searchTerm) {  //<- need to find how to display multiple entries
	auto start = high_resolution_clock::now();
	bool found = false;
	for (int i = 0; i < size; i++) {
		if (uniArr[i].Location == searchTerm) {
			cout << "Rank: " << uniArr[i].Rank << endl;
			cout << "Inistitution: " << uniArr[i].Insitution << endl;
			cout << "Location Code: " << uniArr[i].LocationCode << endl;
			cout << "Location: " << uniArr[i].Location << endl;
			cout << "Academic Reputation Score: " << uniArr[i].ArScore << endl;
			cout << "Academic Reputation Rank: " << uniArr[i].ArRank << endl;
			cout << "Employer Reputation Score: " << uniArr[i].ErScore << endl;
			cout << "Employer Reputation Rank: " << uniArr[i].ErRank << endl;
			cout << "Faculty/Student Ratio Score: " << uniArr[i].FsrScore << endl;
			cout << "Faculty/Student Ratio Rank: " << uniArr[i].FsrRank << endl;
			cout << "Citations per Faculty Score: " << uniArr[i].CpfScore << endl;
			cout << "Citations per Faculty Rank: " << uniArr[i].CpfRank << endl;
			cout << "International Faculty Ratio Score: " << uniArr[i].IfrScore << endl;
			cout << "International Faculty Ratio Rank: " << uniArr[i].IfrRank << endl;
			cout << "International Student Ratio Score: " << uniArr[i].IsrScore << endl;
			cout << "International Student Ratio Rank: " << uniArr[i].IsrRank << endl;
			cout << "International Research Network Score: " << uniArr[i].IrnScore << endl;
			cout << "International Research Network Rank: " << uniArr[i].IrnRank << endl;
			cout << "Employment Outcome Score: " << uniArr[i].GerScore << endl;
			cout << "Employment Outcome Rank: " << uniArr[i].GerRank << endl;
			cout << "Score Scaled: " << uniArr[i].ScoreScaled << endl;
			cout << "-------------------------------------------------------------------" << endl;
			found = true;
		}
	}
	if (!found) {
		cout << "Location Not Found!" << endl;
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << endl << "Time taken by Linear Search Algorithm: " << duration.count() << " microseconds" << endl;
}

void searchUni() {
	head = NULL;
	int size = 0;
	string Insitution, LocationCode, Location, Rank, ArRank, ErRank, FsrRank, CpfRank, IfrRank, IsrRank, IrnRank, GerRank,
		ArScore, ErScore, FsrScore, CpfScore, IfrScore, IsrScore, IrnScore, GerScore, ScoreScaled;
	string addon;
	UniNode* universities = NULL;
	UniNode* lastUniNode = NULL;

	ifstream file("2023 QS World University Rankings.csv");
	while (file.good()) {
		UniNode* university = new UniNode;
		getline(file, Rank, ',');
		getline(file, Insitution, ',');
		if (Insitution[0] == '"') {
			bool endOfString = false;
			while (endOfString == false) {
				for (int i = 1; i < Insitution.length(); i++) {
					if (Insitution[i] == '"') {
						endOfString = true;
						break;
					}
				}
				if (!endOfString) {
					getline(file, addon, ',');
					Insitution = Insitution + ", " + addon;
				}
			}
			Insitution.erase(0, 1);
			Insitution.erase(Insitution.size() - 1);
		}
		getline(file, LocationCode, ',');
		getline(file, Location, ',');
		if (Location[0] == '"') {
			getline(file, addon, ',');
			Location = Location + ", " + addon;
			Location.erase(0, 1);
			Location.erase(Location.size() - 1);
		}
		getline(file, ArScore, ',');
		getline(file, ArRank, ',');
		getline(file, ErScore, ',');
		getline(file, ErRank, ',');
		getline(file, FsrScore, ',');
		getline(file, FsrRank, ',');
		getline(file, CpfScore, ',');
		getline(file, CpfRank, ',');
		getline(file, IfrScore, ',');
		getline(file, IfrRank, ',');
		getline(file, IsrScore, ',');
		getline(file, IsrRank, ',');
		getline(file, IrnScore, ',');
		getline(file, IrnRank, ',');
		getline(file, GerScore, ',');
		getline(file, GerRank, ',');
		getline(file, ScoreScaled);
		if (Insitution == "Institution") {
			continue;
		}
		else if (Rank == "") {
			break;
		}

		if (ErScore == "") {
			ErScore = "-1";
		}
		if (FsrScore == "") {
			FsrScore = "-1";
		}
		if (CpfScore == "") {
			CpfScore = "-1";
		}
		if (IfrScore == "") {
			IfrScore = "-1";
		}

		if (IfrRank == "601+") {
			IfrRank = "601";
		}
		else if (IfrRank == "") {
			IfrRank = "602";
		}

		if (IsrScore == "") {
			IsrScore = "0";
		}
		if (IsrRank == "601+") {
			IsrRank = "601";
		}
		else if (IsrRank == "") {
			IsrRank = "602";
		}

		if (IrnScore == "") {
			IrnScore = "0";
		}
		if (IrnRank == "601+") {
			IrnRank = "601";
		}
		else if (IrnRank == "") {
			IrnRank = "602";
		}

		if (GerScore == "") {
			GerScore = "0";
		}
		if (GerRank == "601+") {
			GerRank = "601";
		}
		else if (GerRank == "") {
			GerRank = "602";
		}
		if (ScoreScaled == "-") {
			ScoreScaled = "0";
		}

		university->Rank = stoi(Rank);
		university->Insitution = Insitution;
		university->LocationCode = LocationCode;
		university->Location = Location;
		university->ArScore = stod(ArScore);
		university->ArRank = stoi(ArRank);
		university->ErScore = stod(ErScore);
		university->ErRank = stoi(ErScore);
		university->FsrScore = stod(FsrScore);
		university->FsrRank = stoi(FsrRank);
		university->CpfScore = stod(CpfScore);
		university->CpfRank = stoi(CpfRank);
		university->IfrScore = stod(IfrScore);
		university->IfrRank = stoi(IfrRank);
		university->IsrScore = stod(IsrScore);
		university->IsrRank = stoi(IsrRank);
		university->IrnScore = stod(IrnScore);
		university->IrnRank = stoi(IrnRank);
		university->GerScore = stod(GerScore);
		university->GerRank = stoi(GerRank);
		university->ScoreScaled = stod(ScoreScaled);
		university->NextAdd = NULL;

		if (universities == NULL) {
			universities = university;
			lastUniNode = university;
		}
		else {
			lastUniNode->NextAdd = university;
			lastUniNode = university;
		}
		size += 1;

	}
	file.close();

	// convert to array
	UniNode* uniArr = new UniNode[size];
	UniNode* currentNode = universities;
	int index = 0;
	while (currentNode != NULL) {
		uniArr[index] = *currentNode;
		currentNode = currentNode->NextAdd;
		index++;
	}

	//search menu
	int choice, choice2;
	string searchTerm;
	cout << "How would you like to search by?" << endl;
	cout << "1. Search by Institution Name\n2. Search by Location" << endl;
	do {
		cout << "Operation No.: ";
		cin >> choice;
		cin.ignore(1, '\n'); // prevent skipping getline()
		// 1. Institution
		if (choice == 1) {
			cout << "\nInstitution Name: ";
			getline(cin, searchTerm);
			cout << "\nWhich searching algorithm would you like to perform?\n1. Binary Search\n2. Linear Search" << endl;
			do {
				cout << "\nAlgorithm No.: ";
				cin >> choice2;

				if (choice2 == 1) {										//<- Binary Search for Institution
					cout << endl;
					quickSortInst(uniArr, 0, size - 1);
					binarySearchInst(uniArr, size, searchTerm);
				}
				else if (choice2 == 2) {								//<- Linear Search for Institution
					cout << endl;
					linearSearchInst(uniArr, size, searchTerm);
				}
				else {
					cout << endl << "Invalid Input" << endl;
				}
			} while (choice2 != 1 && choice2 != 2);
		}
		//2. Location
		else if (choice == 2) {
			cout << "\nLocation: ";
			getline(cin, searchTerm);
			cout << "\nWhich searching algorithm would you like to perform?\n1. Binary Search\n2. Linear Search" << endl;
			do {
				cout << "\nAlgorithm No.: ";
				cin >> choice2;

				if (choice2 == 1) {										//<- Binary Search for Location
					cout << endl;
					quickSortLoc(uniArr, 0, size - 1);
					displayInfoByLoc(uniArr, size, searchTerm);
				}
				else if (choice2 == 2) {								//<- Linear Search for Location
					cout << endl;
					linearSearchLoc(uniArr, size, searchTerm);
				}
				else {
					cout << endl << "Invalid Input" << endl;
				}
			} while (choice2 != 1 && choice2 != 2);
		}
		else {
			cout << endl << "Invalid Input. Please Try Again." << endl << endl;
		}
	} while (choice != 1 && choice != 2);


}

int main() {
	searchUni();
}
