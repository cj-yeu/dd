#include <iostream>
#include <string>
#include <map>      // For membership levels
#include <iomanip>  // For output manipulators

using namespace std;

const int MAX_EVENTS = 100;          // Maximum number of events a user can register for
const int MAX_INTERACTIONS = 100;    // Maximum number of interactions
const int MAX_PACKAGES = 10;         // Maximum number of packages
const int MAX_ADVERTISEMENTS = 10;   // Maximum number of advertisements

class Event; // Forward declaration


struct EventSchedule {
    string time;
    string activity;
    string responsiblePerson;
};

class User {
public:
    string name;
    string email;
    string contact;
    string eventDate;
    int numGuests;           // Number of guests the user is bringing
    string packageType;
    bool isMember;           // Indicates if the user is a member
    string pastEvents[MAX_EVENTS];
    int pastEventCount;
    string interactions[MAX_INTERACTIONS];
    int interactionCount;
    int loyaltyPoints;

    User(const string& name = "", const string& email = "", const string& contact = "", const string& packageType = "", int numGuests = 0, bool isMember = false)
        : name(name), email(email), contact(contact), packageType(packageType), numGuests(numGuests), isMember(isMember), loyaltyPoints(0), pastEventCount(0), interactionCount(0) {
    }

    // Record any event the user has registered for, including the event name and date.
    void addEvent(const string& eventName) {
        if (pastEventCount < MAX_EVENTS) {
            pastEvents[pastEventCount++] = eventName;
        }
    }

    // Record the interaction of the user registering for an event.
    void addInteraction(const string& interaction) {
        if (interactionCount < MAX_INTERACTIONS) {
            interactions[interactionCount++] = interaction;
        }
    }

 

    void displayProfile() const {
        cout << "\n-------- Customer Profile --------\n";
        cout << "Name: " << name << "\n";
        cout << "Email: " << email << "\n";
        cout << "Loyalty Points: " << loyaltyPoints << "\n";
        cout << "Past Events:\n";
        for (int i = 0; i < pastEventCount; ++i) {
            cout << " - " << pastEvents[i] << "\n";
        }
        cout << "----------------------------------\n";
    }
};

class Event {
private:
    int maxGuests;                      // Total maximum guests allowed for the event
    map<string, double> membershipDiscounts;
    map<string, string> packageThemes;
    map<string, bool> bookedDates; // Map to store booked dates
   
    // Add these data members for report generation
    static const int MAX_REGISTRATIONS = 100;
    struct Registration {
        string userName;
        string eventDate;
        string packageType;
        int numGuests;
        double packagePrice;
        double advertisementPrice;
        bool isMember;
    };
    Registration registrations[MAX_REGISTRATIONS];
    int registrationCount;


public:
    Event(int maxGuests = 500);

    void registration(User& user, double packagePrices[], int& packageCount, double advertisementPrices[], int& advertisementCount);

    void sendConfirmation(const User& user) {
        cout << "\nSending confirmation to " << user.email << "...\n";
        cout << "----------------------------------------\n";
        cout << "Dear " << user.name << ",\n";
        cout << "Thank you for registering for the event!\n";
        cout << "Your event will be held on " << user.eventDate << "!\n";
        cout << "We look forward to seeing you there.\n";
        cout << "----------------------------------------\n";
    }


    double package(User& user);

    

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

    double advertisement(const User& user, const string& babyName, const string& time, const string& location);

    void manageLogistics(User& user) {
        cout << "\nManaging logistics for event on " << user.eventDate << "...\n";

        // Check if the date is already booked
        if (bookedDates[user.eventDate]) {
            cout << "Error: The venue is already booked on " << user.eventDate << ".\n";
            // Provide options to reschedule or cancel
        }
        else {
            // Book the date
            bookedDates[user.eventDate] = true;
            cout << "Venue booked successfully for " << user.eventDate << ".\n";
        }

        // Create event schedule
        const int MAX_SCHEDULE_ITEMS = 10;
        EventSchedule schedule[MAX_SCHEDULE_ITEMS];
        int scheduleCount = 0;

        // Add schedule items
        schedule[scheduleCount++] = { "10:00 AM", "Venue Setup", "Alice" };
        schedule[scheduleCount++] = { "12:00 PM", "Decoration", "Bob" };
        schedule[scheduleCount++] = { "02:00 PM", "Guest Arrival", "Event Team" };
        // Add more activities as needed

        // Display event schedule
        cout << "\nEvent Schedule:\n";
        cout << "----------------------------------------\n";
        cout << setw(10) << "Time" << setw(20) << "Activity" << setw(20) << "Responsible\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < scheduleCount; ++i) {
            cout << setw(10) << schedule[i].time
                << setw(20) << schedule[i].activity
                << setw(20) << schedule[i].responsiblePerson << "\n";
        }
        cout << "----------------------------------------\n";
    }
    

    
    void Payment(User& currentUser, const double packagePrices[], int packageCount, const double advertisementPrices[], int advertisementCount);
    
    void generateReport();

};


Event::Event(int maxGuests) : maxGuests(maxGuests), registrationCount(0) {
    membershipDiscounts["Basic"] = 0.0;
    membershipDiscounts["Silver"] = 0.05;   // 5% discount
    membershipDiscounts["Gold"] = 0.10;     // 10% discount
    membershipDiscounts["Platinum"] = 0.15; // 15% discount

    packageThemes["Basic Package"] = "Rainbow Baby Shower";
    packageThemes["Classic Package"] = "Peace and Love Baby Shower";
    packageThemes["Premium Package"] = "Fairytale Baby Shower";
    packageThemes["Luxury Package"] = "The Adventure Begin Baby Shower";
}



void Event::registration(User& user, double packagePrices[], int& packageCount, double advertisementPrices[], int& advertisementCount) {
    cout << "------------------- Event Registration -------------------\n";
    cout << "Registered Name: " << user.name << "\n";
    cout << "Registered Email: " << user.email << "\n";
    cout << "Registered Contact: " << user.contact << "\n";
    cout << "Enter the event date (e.g., 2023-12-31): ";
    getline(cin, user.eventDate);

    user.addEvent("Event on " + user.eventDate); // Add the event with the date to the user's past events

    // Increment loyalty points for each event registration
    user.loyaltyPoints += 10;

    cout << "\nRegistration successful!\n";
    sendConfirmation(user);
    cout << endl;

    // Proceed to package selection
    double packagePrice = package(user);

    if (packagePrice == 0.0) {
        cout << "Package selection failed. Returning to main menu.\n";
        return;
    }

    // Add package price to the array
    packagePrices[packageCount++] = packagePrice;

    // Proceed to advertisement
    double advertisementPrice = 0.0;
    int advertisementChoice;
    cout << "Do you want to advertise your event (RM200)?\n";
    cout << "Press 1 for Yes and 2 for No: ";
    cin >> advertisementChoice;
    cin.ignore();

    if (advertisementChoice == 1) {
        string babyName, time, location;
        cout << "Enter baby name: ";
        getline(cin, babyName);
        cout << "Enter time: ";
        getline(cin, time);
        cout << "Enter location: ";
        getline(cin, location);

        advertisementPrice = advertisement(user, babyName, time, location);
    }
    else {
        cout << "Advertisement not selected.\n";
    }

    // Add advertisement price to the array
    advertisementPrices[advertisementCount++] = advertisementPrice;

    // Store registration data for report
    if (registrationCount < MAX_REGISTRATIONS) {
        registrations[registrationCount].userName = user.name;
        registrations[registrationCount].eventDate = user.eventDate;
        registrations[registrationCount].packageType = user.packageType;
        registrations[registrationCount].numGuests = user.numGuests;
        registrations[registrationCount].packagePrice = packagePrice;
        registrations[registrationCount].advertisementPrice = advertisementPrice;
        registrations[registrationCount].isMember = user.isMember;
        registrationCount++;
    }
    else {
        cout << "Maximum number of registrations reached.\n";
    }

    // Ask if the user wants to add another event
    char addAnother;
    cout << "Do you want to add another event? (Y/N): ";
    cin >> addAnother;
    cin.ignore();

    if (addAnother == 'Y' || addAnother == 'y') {
        registration(user, packagePrices, packageCount, advertisementPrices, advertisementCount);
    }
    else {
        cout << "Proceeding to payment...\n";
        Payment(user, packagePrices, packageCount, advertisementPrices, advertisementCount);
    }
}


double Event::package(User& user) {
    int packageChoice, numGuests, maxPackageGuests;
    double price = 0.0;
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
    cout << " - A photo booth with instant photo prints with customized frames\n";
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
            cout << "Invalid choice. Please choose again.\n";
            packageChoice = 0; // Reset choice to continue loop
        }
    } while (packageChoice < 1 || packageChoice > 4);

    cout << "Enter the number of guests (including yourself): ";
    cin >> numGuests;
    cin.ignore(); // Ignore newline character

    if (numGuests > maxPackageGuests) {
        cout << "Number of guests exceeds the limit for " << packageType << ". Please try again.\n";
        return 0.0; // Return 0 price if the number of guests exceeds the limit
    }

    user.packageType = packageType;
    user.numGuests = numGuests;

    string addonType, addonChoice;
    int addonChosen;
    double addonPrice = 0.0;
    bool validInput = false;

    while (!validInput) {
        cout << endl;
        cout << "Do you want to add on? (Yes/No): ";
        cin >> addonChoice;

        if (addonChoice == "Yes" || addonChoice == "YES" || addonChoice == "yes") {
            validInput = true;
            cout << "Add on Option: \n";
            cout << "1. Photographer - RM300\n";
            cout << "2. Photobooth - RM350\n";
            cout << "3. Master of Event(MC) - RM450\n";
            cout << "4. None\n";
            cout << "Enter your choice (1-4): ";
            cin >> addonChosen;
            cin.ignore(); // Ignore newline character

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
                validInput = false;
            }
        }
        else if (addonChoice == "No" || addonChoice == "NO" || addonChoice == "no") {
            validInput = true;
            addonType = "";
            addonPrice = 0;
        }
        else {
            cout << "Invalid input. Please enter 'Yes' or 'No'.\n";
        }
    }

    price += addonPrice;

    cout << "Package selected: " << packageType << "\n";
    cout << "Your add on: " << addonType << "\n";
    cout << "Number of guests: " << numGuests << "\n";
    cout << "Total price: RM" << fixed << setprecision(2) << price << "\n";
    cout << "----------------------------------------\n";

    return price;
}

double Event::advertisement(const User& user, const string& babyName, const string& time, const string& location) {
    // Retrieve the theme based on the package
    string theme = packageThemes[user.packageType];

    // Use user.eventDate and user.contact
    string eventDate = user.eventDate;
    string rsvpContact = user.contact;

    // Display the advertisement
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
    cout << "RSVP Contact: " << rsvpContact << " for more info.\n\n";
    cout << "Let's make this day special and unforgettable for " << babyName << "'s parents!\n";
    cout << "------------------------------------------------------------------------------------\n";
    cout << endl;

    // Wait for user confirmation
    int chosen;
    cout << "Press 1 to continue: ";
    cin >> chosen;

    while (chosen != 1) {
        cout << "Invalid input. Please try again.\n";
        cout << "Press 1 to continue: ";
        cin >> chosen;
    }

    return 200.0; // Advertisement price
}

void Event::Payment(User& currentUser, const double packagePrices[], int packageCount, const double advertisementPrices[], int advertisementCount) {
    int paymentChoice;
    double totalPackagePrice = 0.0;
    double totalAdvertisementPrice = 0.0;

    // Calculate total package and advertisement prices
    for (int i = 0; i < packageCount; ++i) {
        if (packagePrices[i] > 0.0) {
            totalPackagePrice += packagePrices[i];
        }
    }
    for (int i = 0; i < advertisementCount; ++i) {
        if (advertisementPrices[i] > 0.0) {
            totalAdvertisementPrice += advertisementPrices[i];
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
    for (int i = 0; i < currentUser.pastEventCount; ++i) {
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
    cin.ignore();

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
        break;
    case 2:
        cout << endl;
        cout << "You have selected Touch 'n Go (TNG) Wallet.\n";
        cout << "Enter your TNG Wallet ID: ";
        getline(cin, walletID);
        cout << "Processing payment of RM" << fixed << setprecision(2) << amount << " via TNG Wallet...\n";
        cout << "Payment successful! Thank you.\n";
        break;
    case 3:
        cout << endl;
        cout << "You have selected FPX (Online Banking).\n";
        cout << "Available Banks:\n";
        cout << "1. Maybank\n";
        cout << "2. CIMB\n";
        cout << "3. Public Bank\n";
        cout << "Enter your bank choice (1-3): ";
        cin >> bankChoice;
        cin.ignore();
        cout << "Redirecting to bank choice " << bankChoice << " online banking portal...\n";
        cout << "Confirming payment of RM" << fixed << setprecision(2) << amount << "...\n";
        cout << "Payment successful! Thank you.\n";
        break;
    default:
        cout << "Invalid payment method. Please try again.\n";
        return;
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
    cout << left << setw(30) << "Advertisement" << setw(20) << fixed << setprecision(2) << totalAdvertisementPrice << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(30) << "Subtotal" << setw(20) << fixed << setprecision(2) << subtotal << "\n";
    cout << left << setw(30) << "Member Discount (" << membershipDiscount * 100 << "%)" << setw(20) << fixed << setprecision(2) << subtotal * membershipDiscount << "\n";
    cout << "----------------------------------------\n";
    cout << left << setw(30) << "Total" << setw(20) << fixed << setprecision(2) << amount << "\n";
    cout << "----------------------------------------\n";
    cout << "Invoice sent to " << currentUser.email << "\n";

    int chosen;
    cout << "Press 1 to continue: ";
    cin >> chosen;

    while (chosen != 1) {
        cout << "Invalid input. Please try again.\n";
        cout << "Press 1 to continue: ";
        cin >> chosen;
    }
}

void Event::generateReport() {
    cout << "\nGenerating detailed report...\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(15) << "User Name"
        << setw(15) << "Event Date"
        << setw(20) << "Package Type"
        << setw(10) << "Guests"
        << setw(15) << "Package Price"
        << setw(20) << "Advt. Price"
        << setw(15) << "Member Status" << "\n";
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    double totalRevenue = 0.0;
    int totalGuests = 0;
    int memberCount = 0;
    int nonMemberCount = 0;
    map<string, int> packageSales;

    for (int i = 0; i < registrationCount; ++i) {
        cout << left << setw(15) << registrations[i].userName
            << setw(15) << registrations[i].eventDate
            << setw(20) << registrations[i].packageType
            << setw(10) << registrations[i].numGuests
            << setw(15) << fixed << setprecision(2) << registrations[i].packagePrice
            << setw(20) << registrations[i].advertisementPrice
            << setw(15) << (registrations[i].isMember ? "Member" : "Non-Member") << "\n";

        totalRevenue += registrations[i].packagePrice + registrations[i].advertisementPrice;
        totalGuests += registrations[i].numGuests;

        if (registrations[i].isMember) {
            memberCount++;
        }
        else {
            nonMemberCount++;
        }

        packageSales[registrations[i].packageType]++;
    }
    cout << "-------------------------------------------------------------------------------------------------------------\n";
    cout << "Total Events: " << registrationCount << "\n";
    cout << "Total Guests: " << totalGuests << "\n";
    cout << "Total Revenue: RM" << fixed << setprecision(2) << totalRevenue << "\n";
    cout << "Members: " << memberCount << " | Non-Members: " << nonMemberCount << "\n";
    cout << "Package Sales Breakdown:\n";
    for (const auto& package : packageSales) {
        cout << " - " << package.first << ": " << package.second << " sales\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------------\n";
}






void login(User& user, bool& isStaff) {
    int userType;
    string username, password;

    cout << "Login as:\n";
    cout << "1. Staff\n";
    cout << "2. Customer\n";
    cout << "Enter your choice: ";
    cin >> userType;
    cin.ignore();

    if (userType == 1) {
        isStaff = true;
        // Simulate staff login
        cout << "\nEnter staff username: ";
        getline(cin, username);
        cout << "Enter staff password: ";
        getline(cin, password);
        cout << "Staff login successful.\n";
    }
    else if (userType == 2) {
        isStaff = false;
        cout << "\nEnter your name: ";
        getline(cin, user.name);
        cout << "Enter your email: ";
        getline(cin, user.email);
        cout << "Enter your contact: ";
        getline(cin, user.contact);
        cout << "Login successful.\n";

        string memberResponse, registerMember;
        cout << "\nAre you a member? (yes/no): ";
        cin >> memberResponse;
        user.isMember = (memberResponse == "yes" || memberResponse == "YES" || memberResponse == "Yes");
        cin.ignore();

        if (user.isMember) {
            user.loyaltyPoints += 10; // Add loyalty points for the member
        }
        else {
            cout << "You are not a member. Would you like to sign up for our membership program? (yes/no): ";
            cin >> registerMember;
            cin.ignore();
            if (registerMember == "yes" || registerMember == "YES" || registerMember == "Yes") {
                user.loyaltyPoints += 10;
                user.isMember = true;
            }
            else {
                cout << "Thank you for your interest in our membership program!\n";
            }
        }
    }
    else {
        cout << "Invalid choice. Please try again.\n";
        return;
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
    cin.ignore();

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

    User user;
    bool isStaff = false;
    Event event;
    int choice;
    double packagePrices[MAX_PACKAGES] = { 0 };
    double advertisementPrices[MAX_ADVERTISEMENTS] = { 0 };
    int packageCount = 0;
    int advertisementCount = 0;

    while (true) {
        login(user, isStaff);

        if (isStaff) {
            // Staff menu
            do {
                cout << endl;
                cout << "--------------------------------------" << endl;
                cout << "\t\tStaff Menu\t\t" << endl;
                cout << "--------------------------------------" << endl;
                cout << "1. Event Booking on Dates & Logistics\n"
                    << "2. Event Reporting\n"
                    << "3. Back to Main Menu\n"
                    << "4. Exit\n";
                cout << "--------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1:
                    event.manageLogistics(user);
                    break;
                case 2:
                    event.generateReport();
                    break;
                case 3:
                    break; // Break out of the staff menu loop to re-login
                case 4:
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }

            } while (choice != 3);
        }
        else {
            // Customer menu
            do {
                cout << endl;
                cout << "--------------------------------------" << endl;
                cout << "\t\tCustomer Menu\t\t" << endl;
                cout << "--------------------------------------" << endl;
                cout << "1. Event Registration\n"
                    << "2. Advertisement\n"
                    << "3. CRM/Membership\n"
                    << "4. Back to Main Menu\n"
                    << "5. Exit\n"; 
                cout << "--------------------------------------" << endl;
                cout << "Enter your choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                case 1:
                    event.registration(user, packagePrices, packageCount, advertisementPrices, advertisementCount);
                    break;

                case 2: {
                    string babyName, time, location;
                    cout << "Enter baby name: ";
                    getline(cin, babyName);
                    cout << "Enter time: ";
                    getline(cin, time);
                    cout << "Enter location: ";
                    getline(cin, location);
                    advertisementPrices[advertisementCount++] = event.advertisement(user, babyName, time, location);
                    break;
                }

                case 3: {
                    int crmChoice;

                    do {
                        cout << "\n--------------------------------------" << endl;
                        cout << "1. Customer Profiles\n"
                            << "2. Membership Program\n"
                            << "3. Back to Customer Menu\n";
                        cout << "--------------------------------------" << endl;
                        cout << "Enter your choice: ";
                        cin >> crmChoice;
                        cin.ignore();

                        switch (crmChoice) {
                        case 1:
                            user.displayProfile();
                            break;
                        case 2:
                            event.membership(user);
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                        }
                    } while (crmChoice != 3);
                    break;
                }
                case 4:
                    break; // Break out of the customer menu loop to re-login
                case 5:
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
                }

            } while (choice != 4);
        }
    }

    return 0;
}




























