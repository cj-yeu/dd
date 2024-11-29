#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For output manipulators

using namespace std;

class User {
public:
    string name;
    string email;
    string preferences;
    int numGuests;           // Number of guests the user is bringing
    string packageType;
    bool isMember;           // Indicates if the user is a member

    User(const string& name, const string& email, const string& packageType, int numGuests, bool isMember, const string& preferences = "")
        : name(name), email(email), packageType(packageType), numGuests(numGuests), isMember(isMember), preferences(preferences) {
    }
};

class Event {
private:
    int maxGuests;                      // Total maximum guests allowed for the event

public:
    Event(int maxGuests = 500) : maxGuests(maxGuests) {}
    

    void registration() {
        string name, email, preferences, packageType;
        int packageChoice, numGuests, maxPackageGuests;
        bool isMember;
        double price, discountedPrice;

        cout << "------------------- Event Registration -------------------\n";
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your preferences (optional): ";
        getline(cin, preferences);

        cout << "Are you a member? (yes/no): ";
        string memberResponse;
        getline(cin, memberResponse);
        isMember = (memberResponse == "yes");

        cout << "\nSelect Package Type:\n";
        cout << "1. Basic Package (up to 30 guests) - RM250\n";
        cout << "2. Classic Package (up to 50 guests) - RM500\n";
        cout << "3. Premium Package (up to 100 guests) - RM1000\n";
        cout << "4. Luxury Package (100 guests or more) - RM2500\n";
        cout << "Enter your choice: ";
        cin >> packageChoice;

        switch (packageChoice) {
        case 1:
            maxPackageGuests = 30;
            packageType = "Basic Package";
            price = 250;
            break;
        case 2:
            maxPackageGuests = 50;
            packageType = "Classic Package";
            price = 500;
            break;
        case 3:
            maxPackageGuests = 100;
            packageType = "Premium Package";
            price = 1000;
            break;
        case 4:
            maxPackageGuests = maxGuests; // No upper limit
            packageType = "Luxury Package";
            price = 2500;
            break;
        default:
            cout << "Invalid choice. Defaulting to Basic Package.\n";
            maxPackageGuests = 30;
            packageType = "Basic Package";
            price = 250;
        }

        cout << "Enter the number of guests (including yourself): ";
        cin >> numGuests;
        cin.ignore(); // Ignore newline character

        if (numGuests > maxPackageGuests) {
            cout << "Number of guests exceeds the limit for " << packageType << ". Please try again.\n";
            return;
        }

        if (isMember) {
            discountedPrice = price * 0.9; // Apply 10% discount
            cout << "As a member, you get a 10% discount. The discounted price is: RM" << discountedPrice << "\n";
        }
        else {
            discountedPrice = price;
        }

        User newUser(name, email, packageType, numGuests, isMember, preferences);

        cout << "\nRegistration successful!\n";
        cout << "Package Type: " << packageType << "\n";
        cout << "Number of Guests: " << numGuests << "\n";
        cout << "Total Price: RM" << discountedPrice << "\n";
        sendConfirmation(newUser);
    }

    void sendConfirmation(const User& user) {
        // Simulate sending a confirmation email
        cout << "\nSending confirmation to " << user.email << "...\n";
        cout << "----------------------------------------\n";
        cout << "Dear " << user.name << ",\n";
        cout << "Thank you for registering for the event!\n";
        cout << "Package: " << user.packageType << "\n";
        cout << "Number of Guests: " << user.numGuests << "\n";
        cout << "We look forward to seeing you there.\n";
        cout << "----------------------------------------\n";
    }

    void advertisement(const string& babyName, const string& eventDate, const string& time,
        const string& location, const string& theme, const string& rsvpContact) const {
        cout << endl;
        cout << "------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\tEvent Advertisement\n";
        cout << "------------------------------------------------------------------------------------\n";
        cout << "You are Invited to the Sweetest Baby Shower of the Year!\n\n";
        cout << "Join us in celebrating the arrival of Baby " << babyName << "!\n\n";
        cout << "Date: " << eventDate << endl;
        cout << "Time: " << time << endl;
        cout << "Location: " << location << "\n\n";
        cout << "What is in Store?\n";
        cout << "Fun baby-themed games\n";
        cout << "Exciting gift exchanges\n";
        cout << "Delicious treats and refreshments\n\n";
        cout << "Theme: \"" << theme << "\"\n";

        cout << "Dress to match the theme and bring your best smiles!\n\n";
        cout << "RSVP by [Insert Date]\n";
        cout << "Contact " << rsvpContact << " for more info.\n\n";
        cout << "Let's make this day special and unforgettable for " << babyName << "'s parents!\n";
        cout << "------------------------------------------------------------------------------------\n";
        cout << endl;

        int chosen;
        cout << "Press 1 to continue: ";
        cin >> chosen;

        if (chosen == 1) {
            // Continue to menu
        }
        else {
            cout << "Invalid input. Please try again.\n";
            cout << "Press 1 to continue: ";
            cin >> chosen;
        }
    }

    void package() {
        cout << endl;
        cout << "------------------------------------------------------------------------------------\n";
        cout << "\t\t\t\tEvent Packages\n";
        cout << "************************************************************************************\n";
        cout << "1. Basic Package\n";
        cout << "*Price\t\t: RM250\n";
        cout << "*Number of guests: 15 to 30\n";
        cout << "*Theme\t\t: Rainbow Baby Shower\n";
        cout << "*Basic Inclusion:\n";
        cout << " - 2 colors of balloon decorations\n";
        cout << " - Dessert table with 10-inch single tier of round cake, small cupcakes and cookies\n";
        cout << " - Provide plastic tableware\n";
        cout << endl;

        cout << "************************************************************************************\n";
        cout << "2. Classic Package\n";
        cout << "*Price\t\t: RM500\n";
        cout << "*Number of guests\t: 30 to 50\n";
        cout << "*Theme\t\t: Peace and Love Baby Shower\n";
        cout << "*Basic Inclusion:\n";
        cout << " - Theme color garland and polaroid pictures\n";
        cout << " - Dessert table with 10-inch 2 tier of round cake, small cupcakes, cookies and lollipop\n";
        cout << " - Free decorations of paper invitations\n";
        cout << endl;

        cout << "************************************************************************************\n";
        cout << "3. Premium Package\n";
        cout << "*Price\t\t: RM1000\n";
        cout << "*Number of guests: 50 to 100\n";
        cout << "*Theme\t\t: Fairytale Baby Shower\n";
        cout << "*Basic Inclusion:\n";
        cout << " - Elegant balloon arch and personalized backdrop\n";
        cout << " - Dessert table with 12-inch 3 tier of round cake, small cupcakes, cookies and macaron\n";
        cout << " - Free materials for customer to DIY keepsake corner\n";
        cout << endl;

        cout << "************************************************************************************\n";
        cout << "4. Luxury Package\n";
        cout << "*Price\t\t: RM2500\n";
        cout << "*Number of guests: 100\n";
        cout << "*Theme\t\t: The Adventure Begin Baby Shower\n";
        cout << "*Basic Inclusion:\n";
        cout << " - A decorated arch with greenery and compass motifs\n";
        cout << " - Dessert table with 15-inch 3 tier of round cake, small cupcakes, cookies, macaron and donut\n";
        cout << " - A photo booth with instant photo prints with customized frames that read\n\t\"The Adventure Begins - Baby [Last Name]'s shower.\"\n";
        cout << "------------------------------------------------------------------------------------\n";
        cout << endl;

        int chosen;
        cout << "Press 1 to continue: ";
        cin >> chosen;

        if (chosen == 1) {
            // Continue to menu
        }
        else {
            cout << "Invalid input. Please try again.\n";
            cout << "Press 1 to continue: ";
            cin >> chosen;
        }
    }

    void membership() {
        // Implementation remains the same...
    }

    void payment(const string& customerName, double amount) {
        // Implementation remains the same...
    }

    void marketEvent(const string& tagline, const vector<string>& highlights,
        const string& specialOffer, const string& rsvpContact) {
        // Implementation remains the same...
    }

    void manageLogistics() {
        // Implementation remains the same...
    }

    void monitorEvent() {
        // Implementation remains the same...
    }

    void generateReport() {
        // Implementation remains the same...
    }
};

// Function to handle login
void login() {
    int userType;
    string username, password;

    cout << "Login as:\n";
    cout << "1. Staff\n";
    cout << "2. Customer\n";
    cout << "Enter your choice: ";
    cin >> userType;
    cin.ignore(); // To ignore the newline character left in the buffer

    if (userType == 1) {
        cout << "Enter staff username: ";
        getline(cin, username);
        cout << "Enter staff password: ";
        getline(cin, password);
        // Add authentication logic for staff here
        cout << "Staff login successful.\n";
    }
    else if (userType == 2) {
        cout << "Enter customer username: ";
        getline(cin, username);
        cout << "Enter customer password: ";
        getline(cin, password);
        // Add authentication logic for customers here
        cout << "Customer login successful.\n";
    }
    else {
        cout << "Invalid choice. Please try again.\n";
        login(); // Retry login
    }
}

// Main function
int main() {
    int chosen;
    cout << "Welcome to the Event Management System\n";
    cout << "Press 1 to continue or Press 2 to exit: ";
    cin >> chosen;
    cin.ignore(); // Consume the newline character

    if (chosen == 1) {
        // Continue to login
    }
    else if (chosen == 2) {
        cout << "Goodbye!\n";
        return 0;
    }
    else {
        cout << "Invalid input. Please try again.\n";
        return 0;
    }

    /* Call login function */
    login();

    Event event;
    string babyName, eventDate, time, location, theme, rsvpContact;
    int choice;

    do {
        cout << endl;
        cout << "--------------------------------------" << endl;
        cout << "\t\tMENU\t\t" << endl;
        cout << "--------------------------------------" << endl;
        cout << "1. Event Registration\n2. Event Advertisement\n3. Package Details\n"
            << "4. Membership\n5. Payment and Checkout\n6. Event Marketing\n"
            << "7. Event Booking on Dates & Logistics\n8. Event Monitoring\n"
            << "9. Event Reporting\n10. Exit\n";
        cout << "--------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character

        switch (choice) {
        case 1:
            event.registration();
            break;
        case 2:
            cout << "Enter baby name: ";
            getline(cin, babyName);
            cout << "Enter event date: ";
            getline(cin, eventDate);
            cout << "Enter time: ";
            getline(cin, time);
            cout << "Enter location: ";
            getline(cin, location);
            cout << "Enter theme: ";
            getline(cin, theme);
            cout << "Enter RSVP contact: ";
            getline(cin, rsvpContact);
            event.advertisement(babyName, eventDate, time, location, theme, rsvpContact);
            break;
        case 3:
            event.package();
            break;
        case 4:
            event.membership();
            break;
        case 5: {
            string customerName;
            double amount;
            cout << "Enter customer name: ";
            getline(cin, customerName);
            if (customerName.empty()) {
                cout << "Customer name cannot be empty. Please try again.\n";
                break;
            }
            cout << "Enter amount: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Amount must be greater than zero. Please try again.\n";
                cin.ignore();
                break;
            }
            cin.ignore();
            event.payment(customerName, amount);
            break;
        }
        case 6: {
            string tagline, specialOffer;
            vector<string> highlights;
            int numHighlights;

            cout << "Enter event tagline: ";
            getline(cin, tagline);
            cout << "Enter the number of highlights: ";
            cin >> numHighlights;
            cin.ignore();

            for (int i = 0; i < numHighlights; ++i) {
                string highlight;
                cout << "Enter highlight " << i + 1 << ": ";
                getline(cin, highlight);
                highlights.push_back(highlight);
            }

            cout << "Enter special offer: ";
            getline(cin, specialOffer);

            event.marketEvent(tagline, highlights, specialOffer, rsvpContact);
            break;
        }
        case 7:
            event.manageLogistics();
            break;
        case 8:
            event.monitorEvent();
            break;
        case 9:
            event.generateReport();
            break;
        case 10:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 10);

    return 0;
}

