#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

class Transaction {
public:
    string type;
    string category;
    string date;
    double amount;

    Transaction(string t, string c, string d, double a) : type(t), category(c), date(d), amount(a) {}
};

class FinanceManager {
private:
    vector<Transaction> transactions;
    double monthlyBudget;
    string fileName;

public:
    FinanceManager(string file) : monthlyBudget(0.0), fileName(file) {
        loadTransactions();
    }

    void addIncome(string category, string date, double amount) {
        transactions.push_back(Transaction("Income", category, date, amount));
        saveTransactions();
    }

    void addExpense(string category, string date, double amount) {
        transactions.push_back(Transaction("Expense", category, date, amount));
        saveTransactions();
    }

    void viewTransactions() {
        cout << "Date        | Type    | Category       | Amount\n";
        cout << "-----------------------------------------------\n";
        for (const auto &t : transactions) {
            cout << t.date << " | " << setw(7) << t.type << " | " << setw(13) << t.category << " | $" << fixed << setprecision(2) << t.amount << "\n";
        }
    }

    void setMonthlyBudget(double budget) {
        monthlyBudget = budget;
    }

    void trackBudget() {
        double totalExpenses = 0.0;
        for (const auto &t : transactions) {
            if (t.type == "Expense") {
                totalExpenses += t.amount;
            }
        }
        cout << "Monthly Budget: $" << monthlyBudget << "\n";
        cout << "Total Expenses: $" << totalExpenses << "\n";
        if (totalExpenses > monthlyBudget) {
            cout << "Alert: You have exceeded your budget!\n";
        } else {
            cout << "You are within your budget.\n";
        }
    }

    void monthlySummary() {
        double totalIncome = 0.0;
        double totalExpenses = 0.0;
        for (const auto &t : transactions) {
            if (t.type == "Income") {
                totalIncome += t.amount;
            } else if (t.type == "Expense") {
                totalExpenses += t.amount;
            }
        }
        cout << "Monthly Summary:\n";
        cout << "Total Income: $" << totalIncome << "\n";
        cout << "Total Expenses: $" << totalExpenses << "\n";
        cout << "Net Savings: $" << (totalIncome - totalExpenses) << "\n";
    }

    void categoryBreakdown() {
        map<string, double> breakdown;
        double totalExpenses = 0.0;
        for (const auto &t : transactions) {
            if (t.type == "Expense") {
                breakdown[t.category] += t.amount;
                totalExpenses += t.amount;
            }
        }
        cout << "Category Breakdown:\n";
        for (const auto &entry : breakdown) {
            cout << entry.first << ": $" << entry.second << " (" << (entry.second / totalExpenses) * 100 << "%)\n";
        }
    }

    void trendAnalysis() {
        map<string, double> incomeTrend;
        map<string, double> expenseTrend;
        for (const auto &t : transactions) {
            if (t.type == "Income") {
                incomeTrend[t.date] += t.amount;
            } else if (t.type == "Expense") {
                expenseTrend[t.date] += t.amount;
            }
        }
        cout << "Income Trend:\n";
        for (const auto &entry : incomeTrend) {
            cout << entry.first << ": $" << entry.second << "\n";
        }
        cout << "Expense Trend:\n";
        for (const auto &entry : expenseTrend) {
            cout << entry.first << ": $" << entry.second << "\n";
        }
    }

    void saveTransactions() {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const auto &t : transactions) {
                file << t.type << "," << t.category << "," << t.date << "," << t.amount << "\n";
            }
            file.close();
        } else {
            cout << "Error: Unable to save transactions.\n";
        }
    }

    void loadTransactions() {
        ifstream file(fileName);
        if (file.is_open()) {
            string type, category, date;
            double amount;
            while (file >> type >> category >> date >> amount) {
                transactions.push_back(Transaction(type, category, date, amount));
            }
            file.close();
        } else {
            cout << "Error: Unable to load transactions.\n";
        }
    }
};

int main() {
    FinanceManager fm("transactions.txt");
    int choice;
    string category, date;
    double amount, budget;

    do {
        cout << "\nPersonal Finance Management System\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View Transactions\n";
        cout << "4. Set Monthly Budget\n";
        cout << "5. Track Budget\n";
        cout << "6. Monthly Summary\n";
        cout << "7. Category Breakdown\n";
        cout << "8. Trend Analysis\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter income category: ";
                cin >> category;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;
                fm.addIncome(category, date, amount);
                break;
            case 2:
                cout << "Enter expense category: ";
                cin >> category;
                cout << "Enter date (YYYY-MM-DD): ";
                cin >> date;
                cout << "Enter amount: ";
                cin >> amount;
                fm.addExpense(category, date, amount);
                break;
            case 3:
                fm.viewTransactions();
                break;
            case 4:
                cout << "Enter monthly budget: ";
                cin >> budget;
                fm.setMonthlyBudget(budget);
                break;
            case 5:
                fm.trackBudget();
                break;
            case 6:
                fm.monthlySummary();
                break;
            case 7:
                fm.categoryBreakdown();
                break;
            case 8:
                fm.trendAnalysis();
                break;
            case 9:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 9);

    return 0;
}
