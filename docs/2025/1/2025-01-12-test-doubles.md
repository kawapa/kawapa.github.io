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

A fake is an object that replaces real implementations of classes or functions during unit tests. The purpose of a fake is to simulate the behavior of external components in a controlled and predictable way, enabling the testing of specific parts of code in isolation, without relying on actual resources such as databases, APIs, or file systems.

### Example

Consider a system that uses a `Database` class to save data, but a unit test is required that does not depend on a real database. For simplicity, the interface is as follows:

```cpp
class IDatabase {
public:
    virtual void save(const std::string& data) = 0;
    virtual ~Database() = default;
};
```


For testing purposes, a fake database is created that stores data in a vector instead of using a real database:

```cpp
class FakeDatabase : public IDatabase {
public:
    std::vector<std::string> saved_data;

    void save(const std::string& data) override {
        saved_data.push_back(data);
        // Simulate saving to a database
    }

    bool contains(const std::string& data) const {
        return std::find(saved_data.begin(), saved_data.end(), data) != saved_data.end();
    }
};
```

The class that is under test, `DataProcessor`, uses `IDatabase` to save data:

```cpp
class DataProcessor {
private:
    IDatabase& db;
public:
    explicit DataProcessor(IDatabase& database) : db(database) {}

    void processData(const std::string& data) {
        db.save(data);
    }
};
```

During unit testing, a FakeDatabase is provided to the `DataProcessor` to test its behavior without needing a real database. The **arrange** step involves setting up the fake database and the `DataProcessor`. The **act** step calls the method being tested, and the **assert** step verifies that the expected behavior occurred (i.e., the data was saved in the fake database).

```cpp
TEST(DataProcessorTest, ProcessDataStoresDataInFakeDatabase) {
    // Arrange
    FakeDatabase fakeDb;
    DataProcessor processor(fakeDb);

    // Act
    processor.processData("Test data");

    // Assert
    ASSERT_TRUE(fakeDb.contains("Test data"));
    // Check if the data was saved in the FakeDatabase
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