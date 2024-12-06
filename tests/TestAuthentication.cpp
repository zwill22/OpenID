#include "Catch.hpp"

#include "OpenID.hpp"

using namespace OpenID;

using Catch::Matchers::ContainsSubstring;

IDProvider setupIDProvider(
    const std::string & userName,
    const std::string & password,
    const std::string & emailAddress
) {
    IDSettings settings;
    settings.clientID = "59lgg6i7hcnv8kma81rn4i7qbr";
    settings.clientRegion = "eu-west-2";
    settings.userID = userName;
    settings.password = password;
    settings.emailAddress = emailAddress;

    return IDProvider(settings);
}

TEST_CASE("Test IDProvider") {
    constexpr auto userID = "idProviderTestUserName11345";
    constexpr auto password = "RandomPassword#1234";
    constexpr auto emailAddress = "fake_address@email.com";

    APIClient apiClient;

    SECTION("Invalid Password") {
        const auto idProvider = setupIDProvider(userID, "InvalidPassword", emailAddress);

        CHECK_THROWS_WITH(idProvider.signUpUser(), ContainsSubstring("Password did not conform with policy"));
    }

    SECTION("Existing (Unverified) Username") {
        const auto idProvider = setupIDProvider(userID, password, emailAddress);

        CHECK_THROWS_WITH(idProvider.signUpUser(), ContainsSubstring("User already exists"));
        CHECK_NOTHROW(idProvider.resendCode());
        CHECK_THROWS_WITH(
            idProvider.verifyUser("VerificationCode"),
            ContainsSubstring("Invalid verification code provided")
        );
        CHECK_THROWS_WITH(idProvider.passwordAuthenticate(), ContainsSubstring("Incorrect username or password"));
    }

    SECTION("Non-existant user") {
        const auto idProvider = setupIDProvider("randomUserID", password, emailAddress);
        CHECK_THROWS_WITH(
            idProvider.verifyUser("RandomCode"), 
            ContainsSubstring("Invalid verification code provided")
            || ContainsSubstring("Invalid code provided")
        );
        CHECK_NOTHROW(idProvider.resendCode());
        CHECK_THROWS_WITH(
            idProvider.passwordAuthenticate(),
            ContainsSubstring("Incorrect username or password")
        );

        Authentication fakeAuthentication;
        fakeAuthentication.accessToken = "sertyuk2i3877";
        fakeAuthentication.expiryTime = 3600;
        fakeAuthentication.idToken = "2y6rt78y2ugr2if8y920o";
        fakeAuthentication.refreshToken = "mu87yhnjuy765redfghgt65";
        fakeAuthentication.tokenType = "Bearer";

        CHECK_THROWS_WITH(
            idProvider.deleteUser(fakeAuthentication),
            ContainsSubstring("Invalid Access Token")
        ); 
    }
}
