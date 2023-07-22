

## Printowanie XMLa

```cpp
    tinyxml2::XMLPrinter printer;
    missionDynamicListObject->GetSupplementXMLElement()->Accept(&printer);
    std::cout << printer.CStr() << "\n";
```