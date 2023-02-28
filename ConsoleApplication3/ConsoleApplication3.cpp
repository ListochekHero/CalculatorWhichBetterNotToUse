#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//		||
//		350/5+30-170				=	-70		true
//		350/5-170+30				=	-70		true
//		350-125/5*4+35				=	285		true
//		2*(2+1)+(3*(4-3)*(5+6)+2)	=	41		true		
//		36/3+25-9+17*8+32-95/5*3+18	=	157		true
//		-2+ (+2+ 8) +12*				=	

string checkExp(string exp) {
	//проверить строку на приколы
	//как? да хуй знает но как-то
	//ахуеть да?
	exp.erase(remove_if(exp.begin(), exp.end(), isspace), exp.end());
	return exp;
}

double single_action(string exp) {
	char symb = 'q', action[4]{ '/','*','+','-' };
	int symbtrue;
	double first_number, second_number, result;
	for (int i = 1; i < exp.length(); i++) {
		for (int j = 0; j <= 3; j++) {
			if (exp.at(i) == action[j]) {
				symb = action[j];
				symbtrue = i;
				break;
			}
		}
	}
	first_number = stod(exp.substr(0, symbtrue));
	second_number = stod(exp.substr((symbtrue + 1), (exp.length() - symbtrue)));
	switch (symb) {
	case '/':
		result = first_number / second_number;
		break;
	case '*':
		result = first_number * second_number;
		break;
	case '+':
		result = first_number + second_number;
		break;
	case '-':
		result = first_number - second_number;
		break;
	}
	return result;
}

string getActions(string exp, char action[], vector <char>& act_td, vector <int>& act_td_pos, vector <int>& act_td_prio, vector <double>& number) {
	string result;
	int k = 0;
	act_td.clear();
	act_td_pos.clear();
	act_td_prio.clear();
	number.clear();
	for (int i = 0; i <= exp.length() - 1; i++) {
		for (int j = 0; j <= 4; j++) {
			if (exp.at(i) == action[j]) {
				if (i == 0 && j == 2) {
					break;
				}
				else if (i == 0) {
					exp.erase(0, 1);
					break;
				}
				else if (i == exp.length() - 1) {
					exp.erase((exp.length() - 1), 1);
					break;
				}
				else if (exp.at(i + 1) == action[3]) {

				}
				k++;
				act_td.push_back(action[j]);
				act_td_pos.push_back(i);
				if (j == 0 || j == 1) {
					act_td_prio.push_back(1);
				}
				else {
					act_td_prio.push_back(2);
				}
				break;
			}
		}
	}
	if (k == 0 && exp.at(0) == '-') {
		return exp;
	}
	act_td_pos.insert(act_td_pos.begin(), -1);
	act_td_pos.push_back(exp.length());
	for (int i = 0; i < (k + 1); i++) {
		number.push_back(stod(exp.substr(act_td_pos[i] + 1, act_td_pos[i + 1] - act_td_pos[i] - 1)));
	}
	if (act_td.size() == 0) {
		return exp;
	}
	vector<int>::iterator pos = min_element(begin(act_td_prio), end(act_td_prio));
	int index = distance(begin(act_td_prio), pos);
	result.assign(to_string(number[index]) + act_td[index] + (to_string(number[index + 1])));
	exp.replace(act_td_pos[index] + 1, (act_td_pos[index + 2] - (act_td_pos[index] + 1)), to_string(single_action(result)));
	k -= 1;
	if (k == 0) {
		return exp;
	}
	else {
		return getActions(exp, action, act_td, act_td_pos, act_td_prio, number);
	}
}

void getskobochki(string exp, vector<int>& skobochki_prio, vector<int>& skobochki_pos, int k, char action[], vector <char>& act_td, vector <int>& act_td_pos, vector <int>& act_td_prio, vector <double>& number) {
	int count = 1, index_skob;
	string result_skob;
	skobochki_prio.clear();
	skobochki_pos.clear();
	for (int i = 0; i < exp.length(); i++) {
		if (exp.at(i) == '(') {
			count++;
			skobochki_prio.push_back(count);
			skobochki_pos.push_back(i);
		}
		else if (exp.at(i) == ')') {
			count--;
			skobochki_prio.push_back(count);
			skobochki_pos.push_back(i);
		}
	}
	if (skobochki_prio.size() == 0) {
		cout << getActions(exp, action, act_td, act_td_pos, act_td_prio, number);
	}
	else {
		vector<int>::iterator pos_skob = max_element(begin(skobochki_prio), end(skobochki_prio));
		index_skob = distance(begin(skobochki_prio), pos_skob);
		result_skob.assign(exp, skobochki_pos.at(index_skob) + 1, skobochki_pos.at(index_skob + 1) - skobochki_pos.at(index_skob) - 1);
		exp.replace(skobochki_pos[index_skob], (skobochki_pos[index_skob + 1] - (skobochki_pos[index_skob]) + 1), getActions(result_skob, action, act_td, act_td_pos, act_td_prio, number));
		getskobochki(exp, skobochki_prio, skobochki_pos, k, action, act_td, act_td_pos, act_td_prio, number);
	}
}

int main() {
	int k = 0;
	string exp, result, f;
	vector <char> act_td;
	vector <int> act_td_pos, act_td_prio, skobochki_prio, skobochki, skobochki_pos;
	vector <double> number;
	char action[4]{ '/','*','-','+' };
	getline(cin, exp);
	exp = checkExp(exp);
	getskobochki(exp, skobochki_prio, skobochki_pos, k, action, act_td, act_td_pos, act_td_prio, number);

}
