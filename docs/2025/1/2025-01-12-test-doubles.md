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

{% gist 617bdbd66d460d2f6e8f693c77f5896b fake1.cpp %}

For testing purposes, a fake database is created that stores data in a vector instead of using a real database:

{% gist 617bdbd66d460d2f6e8f693c77f5896b fake2.cpp %}

The class that is under test, `DataProcessor`, uses `IDatabase` to save data:

{% gist 617bdbd66d460d2f6e8f693c77f5896b fake3.cpp %}

During unit testing, a FakeDatabase is provided to the `DataProcessor` to test its behavior without needing a real database. The **arrange** step involves setting up the fake database and the `DataProcessor`. The **act** step calls the method being tested, and the **assert** step verifies that the expected behavior occurred (i.e., the data was saved in the fake database).

{% gist 617bdbd66d460d2f6e8f693c77f5896b fake4.cpp %}

---

## Stub

A stub is an object that provides predefined responses to method calls but does not control or verify the flow of the test. It is used to replace a dependency that should return specific results during the test.

Example: A stub can simulate a method that would normally fetch data from an external server, but instead returns a predefined value in the test.

Use case: Stubs are used to provide specific input data in tests and ensure that the unit under test handles the data correctly.

{% gist 617bdbd66d460d2f6e8f693c77f5896b stub1.cpp %}

---

## Mock

A mock is an object that not only mimics a dependency but also allows verification of interactions between the unit under test and the mock. Mocks help ensure that the unit under test interacts with other objects correctly, such as calling methods with the expected arguments.

Example: A mock can check whether the sendEmail() method was called during the test and with the correct arguments.

Use case: Mocks are used to verify that the unit under test interacts with other objects as expected, such as calling methods under specific conditions.

{% gist 617bdbd66d460d2f6e8f693c77f5896b mock1.cpp %}

FOO

<script src="https://gist.github.com/kawapa/617bdbd66d460d2f6e8f693c77f5896b.js?file=fake1.cpp"></script>

FOO

<script src="https://gist.github.com/kawapa/617bdbd66d460d2f6e8f693c77f5896b.js?file=fake2.cpp"></script>

BAR

<script src="https://gist.github.com/kawapa/617bdbd66d460d2f6e8f693c77f5896b.js?file=fake3.cpp"></script>