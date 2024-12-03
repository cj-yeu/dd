#include <iostream>
#include <vector>
#include <string>
#include <map>      // For membership levels
#include <iomanip>  // For output manipulators

using namespace std;

class Event; // Forward declaration

class User {
public:
    string name;
    string email;
    string preferences;
    int numGuests;           // Number of guests the user is bringing
    string packageType;
    bool isMember;           // Indicates if the user is a member
    vector<string> pastEvents;
    vector<string> interactions;
    vector<string> feedbacks;
    int loyaltyPoints;

    User(const string& name = "", const string& email = "", const string& packageType = "", int numGuests = 0, bool isMember = false, const string& preferences = "")
        : name(name), email(email), packageType(packageType), numGuests(numGuests), isMember(isMember), preferences(preferences), loyaltyPoints(0) {
    }


    // record any event the user has registered for, including the event name and date.
    void addEvent(const string& eventName) {
        pastEvents.push_back(eventName);
    }

    //record the interaction of the user registering for an event.
    void addInteraction(const string& interaction) {
        interactions.push_back(interaction);
    }

    void addFeedback(const string& feedback) {
        feedbacks.push_back(feedback);
    }

    void displayProfile() const {
        cout << "\n-------- Customer Profile --------\n";
        cout << "Name: " << name << "\n";
        cout << "Email: " << email << "\n";
        cout << "Preferences: " << preferences << "\n";
        cout << "Loyalty Points: " << loyaltyPoints << "\n";
        cout << "Past Events:\n";
        for (const auto& event : pastEvents) {
            cout << " - " << event << "\n"; // Ensure this line correctly displays each event with the date
        }
        cout << "----------------------------------\n";
    }


    void collectFeedback(User& user) {
        cout << "\nPlease provide your feedback: ";
        string feedback;
        getline(cin, feedback);
        user.addFeedback(feedback);
        cout << "Thank you for your feedback!\n";
    }

};

class Event {
private:
    int maxGuests;                      // Total maximum guests allowed for the event
    map<string, double> membershipDiscounts;

public:
    Event(int maxGuests = 500);

    void registration(User& user);


    void sendConfirmation(const User& user, const string& eventDate) {
        // Simulate sending a confirmation email
        cout << "\nSending confirmation to " << user.email << "...\n";
        cout << "----------------------------------------\n";
        cout << "Dear " << user.name << ",\n";
        cout << "Thank you for registering for the event!\n";
        cout << "Your event will be held on " << eventDate << "!\n";
        cout << "We look forward to seeing you there.\n";
        cout << "----------------------------------------\n";
    }

    double package(User& user);


    void collectFeedback(User& user) {
        cout << "\nPlease provide your feedback: ";
        string feedback;
        getline(cin, feedback);
        user.addFeedback(feedback);
        cout << "Thank you for your feedback!\n";
    }

    void membership(User& user) {
        cout << "\n-------- Membership Details --------\n";
        cout << "Your current loyalty points: " << user.loyaltyPoints << "\n";
        string level = "Basic";
        if (user.loyaltyPoints >= 100) {
            level = "Platinum";
        }
        else if (user.loyaltyPoints >= 50) {
            level = "Gold";
        }
        else if (user.loyaltyPoints >= 20) {
            level = "Silver";
        }
        cout << "Your membership level: " << level << "\n";
        cout << "You are entitled to a discount of " << setprecision(0) << membershipDiscounts[level] * 100 << "% on your total.\n";
        cout << "------------------------------------\n";
    }

    double advertisement(const string& babyName, const string& eventDate, const string& time,
        const string& location, const string& theme, const string& rsvpContact);

    void manageLogistics() {
        cout << "Managing logistics...\n";
        // Simulate logistics management
        cout << "Logistics managed successfully!\n";
    }

    void monitorEvent() {
        cout << "Monitoring event...\n";
        // Simulate event monitoring
        cout << "Event monitored successfully!\n";
    }

    void marketEvent(const string& tagline, const vector<string>& highlights,
        const string& specialOffer, const string& rsvpContact) {
        cout << "Marketing event with tagline: " << tagline << "\n";
        cout << "Highlights:\n";
        for (const auto& highlight : highlights) {
            cout << " - " << highlight << "\n";
        }
        cout << "Special Offer: " << specialOffer << "\n";
        cout << "RSVP Contact: " << rsvpContact << "\n";
        // Simulate event marketing
        cout << "Event marketed successfully!\n";
    }

    void generateReport() {
        cout << "Generating report...\n";
        // Simulate report generation
        cout << "Report generated successfully!\n";
    }

    void Payment(User& currentUser, const vector<double>& packagePrices, const vector<double>& advertisementPrices);



};

Event::Event(int maxGuests) : maxGuests(maxGuests) {
    membershipDiscounts["Basic"] = 0.0;
    membershipDiscounts["Silver"] = 0.05;   // 5% discount
    membershipDiscounts["Gold"] = 0.10;     // 10% discount
    membershipDiscounts["Platinum"] = 0.15; // 15% discount
}

void Event::registration(User& user) {
    string name, email, preferences, eventDate;
    int numGuests, maxPackageGuests;

    cout << "------------------- Event Registration -------------------\n";
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your email: ";
    getline(cin, email);
    cout << "Enter your preferences (optional): ";
    getline(cin, preferences);
    cout << "Enter the event date (e.g., 2023-12-31): ";
    getline(cin, eventDate); // Read the event date

    user.name = name;
    user.email = email;
    user.preferences = preferences;

    user.addEvent("Event on " + eventDate); // Add the event with the date to the user's past events

    // Increment loyalty points for each event registration
    user.loyaltyPoints += 10;

    cout << "\nRegistration successful!\n";
    sendConfirmation(user, eventDate);
    cout << endl;
    int chosen;
    cout << "Press 1 to menu select package: ";
    cin >> chosen;














    while (chosen != 1) {
        cout << "Invalid input. Please try again.\n";
        cout << "Press 1 to menu select package: ";
        cin >> chosen;
    }
}

double Event::package(User& user) {
    int packageChoice, numGuests, maxPackageGuests;
    double price;
    string packageType;

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
    cout << "*Number of guests: 100 and more\n";
    cout << "*Theme\t\t: The Adventure Begin Baby Shower\n";
    cout << "*Basic Inclusion:\n";
    cout << " - A decorated arch with greenery and compass motifs\n";
    cout << " - Dessert table with 15-inch 3 tier of round cake, small cupcakes, cookies, macaron and donut\n";
    cout << " - A photo booth with instant photo prints with customized frames that read\n\t\"The Adventure Begins - Baby [Last Name]'s shower.\"\n";
    cout << "------------------------------------------------------------------------------------\n";
    cout << endl;

    do {
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
            cout << "Invalid choice. Please choose agai b+n.\n";
        }
    } while (packageChoice < 1 || packageChoice > 4);

    cout << "Enter the number of guests (including yourself): ";
    cin >> numGuests;
    cin.ignore(); // Ignore newline character

    if (numGuests > maxPackageGuests) {
        cout << "Number of guests exceeds the limit for " << packageType << ". Please try again.\n";
        return 0.0;
    }

    user.packageType = packageType;
    user.numGuests = numGuests;

    string addonType, addonChoice;
    int addonChosen;
    double addonPrice = 0;
    cout << endl;
    cout << "Do you want to add on? (Yes/No): ";
    cin >> addonChoice;

    if (addonChoice == "Yes" || addonChoice == "YES" || addonChoice == "yes") {
        cout << "Add on Option: \n";
        cout << "1. Photographer - RM300\n";
        cout << "2. Photobooth - RM350\n";
        cout << "3. Master of Event(MC) - RM450\n";
        cout << "4. None\n";
        cout << "Enter your choice(1,2,3): ";
        cin >> addonChosen;

        switch (addonChosen) {
        case 1:
            addonType = "Photographer";
            addonPrice = 300;
            break;
        case 2:
            addonType = "Photobooth";
            addonPrice = 350;
            break;
        case 3:
            addonType = "Master of Event(MC)";
            addonPrice = 450;
            break;
        case 4:
            addonType = "";
            addonPrice = 0;
            break;
        default:
            cout << "Invalid choice. Please choose again.\n";
        }
    }
    else if (addonChoice == "No" || addonChoice == "NO" || addonChoice == "no") {
        addonType = "";
        addonPrice = 0;
    }
    else {
        cout << "Please input the correct words";
    }

    price += addonPrice;

    cout << "Package selected: " << packageType << "\n";
    cout << "Your add on: " << addonType << "\n";
    cout << "Number of guests: " << numGuests << "\n";
    cout << "Total price: RM" << fixed << setprecision(2) << price << "\n";
    cout << "----------------------------------------\n";

    return price;
}

double Event::advertisement(const string& babyName, const string& eventDate, const string& time,
    const string& location, const string& theme, const string& rsvpContact) {
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
    cout << "RSVP Contact " << rsvpContact << " for more info.\n\n";
    cout << "Let's make this day special and unforgettable for " << babyName << "'s parents!\n";
    cout << "------------------------------------------------------------------------------------\n";
    cout << endl;

    int chosen;
    cout << "Press 1 to continue: ";
    cin >> chosen;

    while (chosen != 1) {
        cout << "Invalid input. Please try again.\n";
        cout << "Press 1 to continue: ";
        cin >> chosen;
    }

    return 200.0; // Example advertisement price
}

void Event::Payment(User& currentUser, const vector<double>& packagePrices, const vector<double>& advertisementPrices) {
    int paymentChoice;
    double totalPackagePrice = 0.0;
    double totalAdvertisementPrice = 0.0;
    double totalAddOnPrice = 0.0;

    // Calculate total package and advertisement prices
    for (double price : packagePrices) {
        if (price > 0.0) {
            totalPackagePrice += price;
        }
    }
    for (double price : advertisementPrices) {
        if (price > 0.0) {
            totalAdvertisementPrice += price;
        }
    }

    double amount = totalPackagePrice + totalAdvertisementPrice;
    string couponCode;
    bool validCoupon = false;
    double discount = 0.0;

    // Display event details in a table format
    cout << endl;
    cout << "Event Details:\n";
    cout << "-------------------------------------------------------------------------\n";
    cout << "|" << left << setw(23) << "Event Date" << "|" << setw(23) << "Package Name" << "|" << setw(23) << "Package Price" << "|" << "\n";
    cout << "-------------------------------------------------------------------------\n";
    for (size_t i = 0; i < currentUser.pastEvents.size(); ++i) {
        if (packagePrices[i] > 0.0) {
            cout << "|" << left << setw(23) << currentUser.pastEvents[i] << "|" << setw(23) << currentUser.packageType << "|" << setw(23) << fixed << setprecision(2) << packagePrices[i] << "|" << "\n";
            cout << "-------------------------------------------------------------------------\n";
        }
    }

    // Display membership status and discount rate
    string level = "Basic";
    if (currentUser.loyaltyPoints >= 100) {
        level = "Platinum";
    }
    else if (currentUser.loyaltyPoints >= 50) {
        level = "Gold";
    }
    else if (currentUser.loyaltyPoints >= 20) {
        level = "Silver";
    }
    double membershipDiscount = membershipDiscounts[level];
    cout << endl;
    cout << "----------------------------------------\n";
    cout << "|" << "Membership Status\t: " << (currentUser.isMember ? "Member" : "Non-Member") << "\t|\n";
    cout << "|" << "Membership Level\t: " << level << "\t|\n";
    cout << "|" << "Discount Rate\t\t: " << membershipDiscount * 100 << "%" << "\t\t|\n";
    cout << "----------------------------------------\n";

    // Apply membership discount
    amount = amount * (1 - membershipDiscount);

    cout << endl;
    cout << "Total amount to pay after membership discount: RM" << fixed << setprecision(2) << amount << "\n";

    cout << "Do you have a discount coupon? (yes/no): ";
    string couponResponse;
    getline(cin, couponResponse);
    if (couponResponse == "yes") {
        cout << "Enter coupon code: ";
        getline(cin, couponCode);
        // Validate coupon code (for simplicity, assume "DISCOUNT10" gives a 10% discount)
        if (couponCode == "DISCOUNT10") {
            validCoupon = true;
            discount = 0.10;
        }
        else {
            cout << "Invalid coupon code.\n";
        }
    }

    if (validCoupon) {
        amount = amount * (1 - discount);
        cout << "Discount applied. New amount to pay: RM" << fixed << setprecision(2) << amount << "\n";
    }

    string walletID, cardDetails, cvv;
    int bankChoice;
    cout << "\nChoose payment method:\n";
    cout << "1. Credit/Debit Card\n";
    cout << "2. TNG\n";
    cout << "3. Bank Transfer(FPX)\n";
    cout << "\nEnter your choice: ";
    cin >> paymentChoice;
    cin.ignore(); // Ignore newline character

    switch (paymentChoice) {
    case 1:
        cout << endl;
        cout << "You have selected Credit/Debit Card.\n";
        cout << "Enter your card number: ";
        getline(cin, cardDetails);
        cout << "Enter CVV: ";
        getline(cin, cvv);
        cout << "Processing payment of RM" << fixed << setprecision(2) << amount << " via Credit/Debit Card...\n";
        cout << "Payment successful! Thank you.\n";
        // Simulate payment processing
        break;
    case 2:
        cout << endl;
        cout << "You have selected Touch 'n Go (TNG) Wallet.\n";
        cout << "Enter your TNG Wallet ID: ";
        getline(cin, walletID);
        cout << "Processing payment of RM" << fixed << setprecision(2) << amount << " via TNG Wallet...\n";
        cout << "Payment successful! Thank you.\n";
        // Simulate payment processing
        break;
    case 3:
        cout << endl;
        cout << "You have selected FPX (Online Banking).\n";
        cout << "Available Banks:\n";
        cout << "1. Maybank\n";
        cout << "2. CIMB\n";
        cout << "3. Public Bank\n";
        cout << "Enter your bank name: ";
        cin >> bankChoice;
        cout << "Redirecting to " << bankChoice << " online banking portal...\n";
        cout << "Confirming payment of RM" << fixed << setprecision(2) << amount << "...\n";
        cout << "Payment successful! Thank you.\n";
        // Simulate payment processing
        break;
    default:
        cout << "Invalid payment method. Please try again.\n";
        return; // Exit the function if the payment method is invalid
    }

    cout << endl;
    cout << "Press 1 to generate your invoice: ";
    int invoiceChoice;
    double subtotal = totalPackagePrice + totalAdvertisementPrice;
    cin >> invoiceChoice;
    while (invoiceChoice != 1) {
        cout << "Invalid input. Please try again.\n";
        cout << "Press 1 to generate your invoice: ";
        cin >> invoiceChoice;
    }

    // Calculate add-on price
    totalAddOnPrice = amount - totalPackagePrice - totalAdvertisementPrice;

    // Generate and display invoice
    cout << "\nGenerating invoice...\n";
    cout << "----------------------------------------\n";
    cout << "Invoice\n";
    cout << "----------------------------------------\n";
    cout << "Name: " << currentUser.name << "\n";
    cout << "Email: " << currentUser.email << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(30) << "Description" << setw(20) << "Amount (RM)" << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(30) << "Package(s)" << setw(20) << fixed << setprecision(2) << totalPackagePrice << "\n";
    cout << left << setw(30) << "Add-on(s)" << setw(20) << fixed << setprecision(2) << totalAddOnPrice << "\n";
    cout << left << setw(30) << "Advertisement" << setw(20) << fixed << setprecision(2) << totalAdvertisementPrice << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(30) << "Subtotal" << setw(20) << fixed << setprecision(2) << subtotal << "\n";
    cout << left << setw(30) << "Member Discount (" << membershipDiscount * 100 << "%)" << setw(20) << fixed << setprecision(2) << subtotal * membershipDiscount << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(30) << "Total" << setw(20) << fixed << setprecision(2) << amount << "\n";
    cout << "----------------------------------------\n";
    cout << "Invoice sent to " << currentUser.email << "\n";

    // Refund processing (for simplicity, assume refund is always successful)
    cout << "Do you want to process a refund? (yes/no): ";
    string refundResponse;
    cin.ignore(); // Ignore newline character
    getline(cin, refundResponse);
    if (refundResponse == "yes") {
        cout << "Processing refund...\n";
        cout << "Refund successful!\n";
    }

    int chosen;
    cout << "Press 1 to continue: ";
    cin >> chosen;

    while (chosen != 1) {
        cout << "Invalid input. Please try again.\n";
        cout << "Press 1 to continue: ";
        cin >> chosen;
    }
}





void login(User& user, bool& isStaff) {
    int userType;
    string username, password;

    cout << "Login as:\n";
    cout << "1. Staff\n";
    cout << "2. Customer\n";
    cout << "Enter your choice: ";
    cin >> userType;
    cin.ignore(); // To ignore the newline character left in the buffer

    if (userType == 1) {
        isStaff = true;
        // Simulate staff login
        cout << "Enter staff username: ";
        getline(cin, username);
        cout << "Enter staff password: ";
        getline(cin, password);
        // Add authentication logic for staff here
        cout << "Staff login successful.\n";
    }
    else if (userType == 2) {
        isStaff = false;
        cout << "Login as:\n";
        cout << "1. Existing Customer\n";
        cout << "2. New Customer\n";
        cout << "Enter your choice: ";
        int customerType;
        cin >> customerType;
        cin.ignore(); // To ignore the newline character left in the buffer

        if (customerType == 1) {
            // Simulate customer login
            cout << "Enter your email: ";
            getline(cin, username);
            // For simplicity, assume user exists and fetch user data
            user.email = username;
            cout << "Welcome back, " << username << "!\n";
        }
        else if (customerType == 2) {
            cout << "Proceeding as a new customer.\n";
            // Additional code for new customer registration if needed
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            login(user, isStaff); // Retry login
        }
    }
    else {
        cout << "Invalid choice. Please try again.\n";
        login(user, isStaff); // Retry login
    }
}



// Main function
int main() {
    int chosen;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "    ~~~~~~~~~~ WELCOME TO THE ~~~~~~~~~~~~" << endl;
    cout << "                 ___      __    ___     __     __                   " << endl;
    cout << "                \\  __  \\  .'  _ `.\\  ___  \\   \\   \\   /  /                  " << endl;
    cout << "                | |    \\ | /   '  \\  \\ |    \\ |    \\  _. /  '                   " << endl;
    cout << "                | |_/ / |_|  /  | |_/ /     ( ) .'                    " << endl;
    cout << "                |   _ _ '.    .-`   |   _ _ '. _( o _)'                     " << endl;
    cout << "                |  ( ' )  \\.'.   _    |  ( ' )  \\   |(,)'                      " << endl;
    cout << "                | ({;}) ||  ( )  | ({;}) |   `-'  /                       " << endl;
    cout << "                |  (,)  /\\ (_ o ) /  (,_)  /\\      /                        " << endl;
    cout << "                /__.'  '.(,).'/__.'  `-..-'                         " << endl;
    cout << "   .-'''-. .---.  .---.     ,-----.    .--.      .--.    .-''-.  .-------.     " << endl;
    cout << "  / _     \\|   |  |_ |   .'  .-,  '.  |  |     |  |  .'_ _   \\ |  _ _   \\  " << endl;
    cout << " (' )/--'|   |  ( ' )  / ,-.|  \\ _ \\ | ( )   |  | / ( ` )   '| ( ' )  | " << endl;
    cout << " (_ o ).   |   '-({;});  \\  ' /  | :|(_ o )  |  |. ( o )  ||( o _) /  " << endl;
    cout << " (,). '. |      (,) |  `,/ \\ _/  || (,) \\ |  ||  (,)_|| (,).' _" << endl;
    cout << ".---.  \\  :| _ --.   | : (  '\\/ \\   ;|  |/    \\|  |'  \\   .---.|  |\\ \\  |  |" << endl;
    cout << "\\    `-'  ||( ' ) |   |  \\ `\"/  \\  ) / |  '  /\\  `  | \\  `-'    /|  | \\ `'   /" << endl;
    cout << " \\       / ({;})|   |   '. \\_/``\".'  |    /  \\    |  \\       / |  |  \\    /  " << endl;
    cout << "  -...-'  '(_,_) '---'     '-----'    `---'    `---   `'-..-'  ''-'   `'-'   " << endl;
    cout << "    ~~~~~~~~~~~ EVENT ! ~~~~~~~~~~~~" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;


    cout << endl;
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

    User currentUser;
    bool isStaff = false;
    login(currentUser, isStaff);

    Event event;
    int choice;
    vector<double> packagePrices;
    vector<double> advertisementPrices;

    if (isStaff) {
        // Staff menu
        do {
            cout << endl;
            cout << "--------------------------------------" << endl;
            cout << "\t\tStaff Menu\t\t" << endl;
            cout << "--------------------------------------" << endl;
            cout << "1. Event Booking on Dates & Logistics\n"
                << "2. Event Monitoring\n"
                << "3. Event Marketing\n"
                << "4. Event Reporting\n"
                << "5. Exit\n";
            cout << "--------------------------------------" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Ignore newline character

            switch (choice) {
            case 1:
                event.manageLogistics();
                break;
            case 2:
                event.monitorEvent();
                break;
            case 3: {
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
                string rsvpContact;
                cout << "Enter RSVP contact: ";
                getline(cin, rsvpContact);
                event.marketEvent(tagline, highlights, specialOffer, rsvpContact);
                break;
            }
            case 4:
                event.generateReport();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 5);
    }
    else {
        // Customer menu
        do {
            cout << endl;
            cout << "--------------------------------------" << endl;
            cout << "\t\tCustomer Menu\t\t" << endl;
            cout << "--------------------------------------" << endl;
            cout << "1. Event Registration\n"
                << "2. Package\n"
                << "3. Event Advertisement\n"
                << "4. CRM/Membership\n"
                << "5. Payment\n"
                << "6. Exit\n";
            cout << "--------------------------------------" << endl;
            cout << "Enter your choice: ";
            cin >> choice;
            cin.ignore(); // Ignore newline character

            switch (choice) {
            case 1:
                event.registration(currentUser);
                break;

            case 2:
                packagePrices.push_back(event.package(currentUser));
                break;

            case 3: {
                string babyName, eventDate, time, location, theme, rsvpContact;
                int advertisementChoice;

                cout << "Do you want to advertise your event (RM200)?\n";
                cout << "Press 1 for Yes and 2 for No: ";
                cin >> advertisementChoice;
                cin.ignore(); // Ignore newline character

                do {
                    cout << "Do you want to advertise your event (RM200)?\n";
                    cout << "Press 1 for Yes and 2 for No: ";
                    cin >> advertisementChoice;
                    cin.ignore(); // Ignore newline character

                    if (advertisementChoice == 1) {
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
                        advertisementPrices.push_back(event.advertisement(babyName, eventDate, time, location, theme, rsvpContact));
                    }
                    else if (advertisementChoice == 2) {
                        cout << "Advertisement not selected.\n";
                        advertisementPrices.push_back(0.0); // No advertisement price
                    }
                    else {
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (advertisementChoice != 1 && advertisementChoice != 2);


                break;
            }

            case 4: {
                int crmChoice;
                string memberResponse, registerMember;
                cout << "Are you a member? (yes/no): ";
                cin >> memberResponse;
                currentUser.isMember = (memberResponse == "yes" || memberResponse == "YES" || memberResponse == "Yes");

                if (currentUser.isMember) {
                    currentUser.loyaltyPoints += 10; // Add loyalty points for the member
                }
				else {
					cout << "You are not a member. Would you like to sign up for our membership program? (yes/no): ";
					cin >> registerMember;
                    if (registerMember == "yes" || registerMember == "YES" || registerMember == "Yes") 
                        currentUser.loyaltyPoints += 10; // Add loyalty points for the member
                    else {
                        cout << "Thank you for your interest in our membership program!\n";
                        currentUser.loyaltyPoints += 0; // Add loyalty points for the member
                    }
                }
                    
				

                do {
                    cout << "\n--------------------------------------" << endl;
                    cout << "1. Customer Profiles\n"
                        << "2. Membership Program\n"
                        << "3. Feedback\n"
                        << "4. Back to Customer Menu\n";
                    cout << "--------------------------------------" << endl;
                    cout << "Enter your choice: ";
                    cin >> crmChoice;
                    cin.ignore(); // Ignore newline character

                    switch (crmChoice) {
                    case 1:
                        currentUser.displayProfile();
                        break;
                    case 2:
                        event.membership(currentUser);
                        break;
                    case 3:
                        event.collectFeedback(currentUser);
                        break;
                    case 4:
                        break;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                    }
                } while (crmChoice != 4);
                break;
            }

            case 5:
                event.Payment(currentUser, packagePrices, advertisementPrices);
                break;

            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }

        } while (choice != 6);
    }

    return 0;
}












