---
layout: page
title: Test doubles
date: 2025-01-12
permalink: /test-doubles
---

# Test doubles

In unit testing, it’s often necessary to isolate the unit under test from its dependencies. This is where test doubles like fake, stub, and mock come into play. Each of these objects serves a different purpose, helping to simulate dependencies and control interactions during tests. In this post, we’ll explore the differences between these techniques and how to apply them in practice.

---

## Fake

A fake is an object that mimics a real dependency but is implemented in a simpler way. It is typically used when the real dependency is too complex to implement or when its full functionality is unnecessary for the test.

Example: Instead of using a full database, a fake implementation might be used that keeps data in memory (e.g., in a collection within the application).

Use case: Fakes are useful when the test needs to operate on real data but the full functionality of the external dependency is not required.

```cpp
class IDatabase {
public:
    virtual void save(int data) = 0;
    virtual int get(int index) = 0;
};

class FakeDatabase : public IDatabase {
private:
    std::vector<int> dataStore;
public:
    void save(int data) override {
        dataStore.push_back(data);  // Simulate saving to a database
    }

    int get(int index) override {
        return dataStore[index];  // Simulate retrieving from a database
    }
};

int main() {
    FakeDatabase fakeDb;
    fakeDb.save(42);
}
```

---

## Stub

A stub is an object that provides predefined responses to method calls but does not control or verify the flow of the test. It is used to replace a dependency that should return specific results during the test.

Example: A stub can simulate a method that would normally fetch data from an external server, but instead returns a predefined value in the test.

Use case: Stubs are used to provide specific input data in tests and ensure that the unit under test handles the data correctly.

```cpp
class IExternalService {
public:
    virtual int fetchData() = 0;
};

class StubService : public IExternalService {
public:
    int fetchData() override {
        return 100;  // Return predefined data
    }
};

class Application {
private:
    ExternalService& service;
public:
    Application(ExternalService& svc) : service(svc) {}
    
    void processData() {
        int data = service.fetchData();
    }
};

int main() {
    StubService stubService;
    Application app(stubService);
    app.processData();
}
```

---

## Mock

A mock is an object that not only mimics a dependency but also allows verification of interactions between the unit under test and the mock. Mocks help ensure that the unit under test interacts with other objects correctly, such as calling methods with the expected arguments.

Example: A mock can check whether the sendEmail() method was called during the test and with the correct arguments.

Use case: Mocks are used to verify that the unit under test interacts with other objects as expected, such as calling methods under specific conditions.

```cpp
class IEmailService {
public:
    virtual void sendEmail(const std::string& message) = 0;
};

class MockEmailService : public IEmailService {
public:
    bool wasCalled = false;
    std::string receivedMessage;

    void sendEmail(const std::string& message) override {
        wasCalled = true;
        receivedMessage = message;
    }
};

class UserNotification {
private:
    EmailService& emailService;
public:
    UserNotification(EmailService& service) : emailService(service) {}

    void notify(const std::string& message) {
        emailService.sendEmail(message);
    }
};

int main() {
    MockEmailService mockService;
    UserNotification notification(mockService);

    notification.notify("Test Message");

    assert(mockService.wasCalled == true);
    assert(mockService.receivedMessage == "Test Message");
}
```