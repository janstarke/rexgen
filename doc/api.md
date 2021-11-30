# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`rexgen`](#namespacerexgen) | 
`class `[`GenericError`](#class_generic_error) | 
`class `[`SyntaxError`](#class_syntax_error) | 
`struct `[`_RexgenOptions`](#struct___rexgen_options) | 

# namespace `rexgen` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`enum `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)            | 
`class `[`rexgen::ClassRegex`](#classrexgen_1_1_class_regex) | 
`class `[`rexgen::ClassRegexIterator`](#classrexgen_1_1_class_regex_iterator) | 
`class `[`rexgen::CompoundRegex`](#classrexgen_1_1_compound_regex) | 
`class `[`rexgen::CompoundRegexIterator`](#classrexgen_1_1_compound_regex_iterator) | 
`class `[`rexgen::FastIteratorPermuter`](#classrexgen_1_1_fast_iterator_permuter) | 
`class `[`rexgen::GroupReference`](#classrexgen_1_1_group_reference) | 
`class `[`rexgen::GroupReferenceIterator`](#classrexgen_1_1_group_reference_iterator) | 
`class `[`rexgen::IteratorPermuter`](#classrexgen_1_1_iterator_permuter) | 
`class `[`rexgen::IteratorState`](#classrexgen_1_1_iterator_state) | 
`class `[`rexgen::Quantifier`](#classrexgen_1_1_quantifier) | 
`class `[`rexgen::RangeIterator`](#classrexgen_1_1_range_iterator) | 
`class `[`rexgen::Regex`](#classrexgen_1_1_regex) | 
`class `[`rexgen::RegexAlternatives`](#classrexgen_1_1_regex_alternatives) | 
`class `[`rexgen::RegexAlternativesIterator`](#classrexgen_1_1_regex_alternatives_iterator) | 
`class `[`rexgen::RegexContainer`](#classrexgen_1_1_regex_container) | 
`class `[`rexgen::RexgenFlexLexer`](#classrexgen_1_1_rexgen_flex_lexer) | 
`class `[`rexgen::RexgenOptions`](#classrexgen_1_1_rexgen_options) | 
`class `[`rexgen::RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver) | 
`class `[`rexgen::StreamRegex`](#classrexgen_1_1_stream_regex) | 
`class `[`rexgen::StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator) | 
`class `[`rexgen::TerminalRegex`](#classrexgen_1_1_terminal_regex) | 
`class `[`rexgen::TerminalRegexIterator`](#classrexgen_1_1_terminal_regex_iterator) | 
`class `[`rexgen::TopIterator`](#classrexgen_1_1_top_iterator) | 
`struct `[`rexgen::t_group_options`](#structrexgen_1_1t__group__options) | 

## Members

#### `enum `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
Compound            | 
Alternative            | 
Terminal            | 
Class            | 
Reference            | 
Stream            | 
Range            | 

## class `rexgen::ClassRegex` 

```
class rexgen::ClassRegex
  : public rexgen::Regex
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`addCharacter`](#classrexgen_1_1_class_regex_1a9f79bb8c2b164dfde9f4a09fe8e35128)`(const wchar_t & ch)` | 
`public void `[`addRange`](#classrexgen_1_1_class_regex_1ae6d97d013df908bedd44526a9154da41)`(const wchar_t & a,const wchar_t & b)` | 
`public inline void `[`addRange`](#classrexgen_1_1_class_regex_1a73d81f8dc6904c03487cf1b0a387c17b)`(`[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04)` ct)` | 
`public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`contains`](#classrexgen_1_1_class_regex_1a8fd8793ef16a57ad4e2e6ce1f2199ccc)`(const wchar_t & ch) const` | 
`public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_class_regex_1a2e2dc0b795a7f6871cb447b013b9e83d)`() const` | 
`public void `[`merge`](#classrexgen_1_1_class_regex_1af4cbc57a1069f7c5eae971692f34d279)`(const std::shared_ptr< `[`ClassRegex`](#classrexgen_1_1_class_regex)` > & other)` | 
`public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_class_regex_1a936904b82d3576ca2e08c6f22e69ad9d)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &) const` | 
`public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_class_regex_1af9a894d93cd02d8b831f02223519f1d8)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &) const` | 
`enum `[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04) | 
`private std::set< wchar_t > `[`characters`](#classrexgen_1_1_class_regex_1a833a53ab7b82eda315ea2e0a725969cb) | 
`private std::set< `[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04)` > `[`ranges`](#classrexgen_1_1_class_regex_1aaa64323edc1012980ed1c64dc7dbd67c) | 
`private void `[`removeCharacterInstances`](#classrexgen_1_1_class_regex_1ac00ade8bc5772396ee5a5efd615d281c)`(const wchar_t min,const wchar_t max)` | 
`private void `[`removeCharacterInstances`](#classrexgen_1_1_class_regex_1a469bfdc75ba95acd6482622aca321cd6)`(`[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04)` ct)` | 
`private void `[`minimize`](#classrexgen_1_1_class_regex_1a493566c317ffbbfba18fc6659c87da99)`()` | 

### Members

#### `public void `[`addCharacter`](#classrexgen_1_1_class_regex_1a9f79bb8c2b164dfde9f4a09fe8e35128)`(const wchar_t & ch)` 

#### `public void `[`addRange`](#classrexgen_1_1_class_regex_1ae6d97d013df908bedd44526a9154da41)`(const wchar_t & a,const wchar_t & b)` 

#### `public inline void `[`addRange`](#classrexgen_1_1_class_regex_1a73d81f8dc6904c03487cf1b0a387c17b)`(`[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04)` ct)` 

#### `public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`contains`](#classrexgen_1_1_class_regex_1a8fd8793ef16a57ad4e2e6ce1f2199ccc)`(const wchar_t & ch) const` 

#### `public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_class_regex_1a2e2dc0b795a7f6871cb447b013b9e83d)`() const` 

#### `public void `[`merge`](#classrexgen_1_1_class_regex_1af4cbc57a1069f7c5eae971692f34d279)`(const std::shared_ptr< `[`ClassRegex`](#classrexgen_1_1_class_regex)` > & other)` 

#### `public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_class_regex_1a936904b82d3576ca2e08c6f22e69ad9d)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &) const` 

#### `public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_class_regex_1af9a894d93cd02d8b831f02223519f1d8)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &) const` 

#### `enum `[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04) 

 Values                         | Descriptions                                
--------------------------------|---------------------------------------------
DIGITS            | 
UPPERCASE            | 
LOWERCASE            | 
WORDCHARACTERS            | 
SPACES            | 

#### `private std::set< wchar_t > `[`characters`](#classrexgen_1_1_class_regex_1a833a53ab7b82eda315ea2e0a725969cb) 

#### `private std::set< `[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04)` > `[`ranges`](#classrexgen_1_1_class_regex_1aaa64323edc1012980ed1c64dc7dbd67c) 

#### `private void `[`removeCharacterInstances`](#classrexgen_1_1_class_regex_1ac00ade8bc5772396ee5a5efd615d281c)`(const wchar_t min,const wchar_t max)` 

#### `private void `[`removeCharacterInstances`](#classrexgen_1_1_class_regex_1a469bfdc75ba95acd6482622aca321cd6)`(`[`CharacterClassType`](#classrexgen_1_1_class_regex_1ae3d4d058364030e9fd5338c6a3971b04)` ct)` 

#### `private void `[`minimize`](#classrexgen_1_1_class_regex_1a493566c317ffbbfba18fc6659c87da99)`()` 

## class `rexgen::ClassRegexIterator` 

```
class rexgen::ClassRegexIterator
  : public Iterator
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public template<>`  <br/>`inline  `[`ClassRegexIterator`](#classrexgen_1_1_class_regex_iterator_1aff44d7036c564b3caaa183c286538a1c)`(Iter begin,Iter end)` | 
`public inline virtual  `[`~ClassRegexIterator`](#classrexgen_1_1_class_regex_iterator_1ad53f0260b7655dfc9d11cd5752cf25f0)`()` | 
`public inline virtual void `[`updateReferences`](#classrexgen_1_1_class_regex_iterator_1a36428360366911f1ca2d9215741a3def)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline virtual void `[`updateAttributes`](#classrexgen_1_1_class_regex_iterator_1ac330e2d44ebf2a8cc8a3fe308ea606f6)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline void `[`value`](#classrexgen_1_1_class_regex_iterator_1a31ab34a29bd365b8df301cc3c07f287c)`(SimpleString * dst) const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_class_regex_iterator_1aca263dfcfb5a368ac76a4d6604856e7e)`()` | 
`public inline size_t `[`size`](#classrexgen_1_1_class_regex_iterator_1a430a09ffbd4f059c8d1a591499fbf7ed)`() const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_class_regex_iterator_1aa25ddc276c2fcdaa151974da64d717b8)`() const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`canUseValue`](#classrexgen_1_1_class_regex_iterator_1a0efb156682be30fd85ad09dee8ba73a5)`() const` | 
`public inline std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_class_regex_iterator_1a96d8d9f201e731f5efbceaf2661a90c4)`() const` | 
`public inline void `[`setCurrentState`](#classrexgen_1_1_class_regex_iterator_1a90e36aa2d1f5a1e344350163c8d38c7e)`(const std::shared_ptr< SerializableState > & s)` | 
`private signed int `[`current`](#classrexgen_1_1_class_regex_iterator_1aff1a477f0e0dad7fe44ef069e61bbe43) | 
`private int `[`characters_count`](#classrexgen_1_1_class_regex_iterator_1aab27ad37bbb32f13229951861dbc186a) | 
`private SimpleString `[`characters`](#classrexgen_1_1_class_regex_iterator_1a4f718f9914d9e6689d33be7afbf04808) | 
`private vector< std::string::size_type > `[`indices`](#classrexgen_1_1_class_regex_iterator_1a55855dbd631cc6b77880061231645697) | 
`private vector< std::string::size_type > `[`lengths`](#classrexgen_1_1_class_regex_iterator_1a79c1926e759f777e39026d38dbc26d90) | 

### Members

#### `public template<>`  <br/>`inline  `[`ClassRegexIterator`](#classrexgen_1_1_class_regex_iterator_1aff44d7036c564b3caaa183c286538a1c)`(Iter begin,Iter end)` 

#### `public inline virtual  `[`~ClassRegexIterator`](#classrexgen_1_1_class_regex_iterator_1ad53f0260b7655dfc9d11cd5752cf25f0)`()` 

#### `public inline virtual void `[`updateReferences`](#classrexgen_1_1_class_regex_iterator_1a36428360366911f1ca2d9215741a3def)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline virtual void `[`updateAttributes`](#classrexgen_1_1_class_regex_iterator_1ac330e2d44ebf2a8cc8a3fe308ea606f6)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline void `[`value`](#classrexgen_1_1_class_regex_iterator_1a31ab34a29bd365b8df301cc3c07f287c)`(SimpleString * dst) const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_class_regex_iterator_1aca263dfcfb5a368ac76a4d6604856e7e)`()` 

#### `public inline size_t `[`size`](#classrexgen_1_1_class_regex_iterator_1a430a09ffbd4f059c8d1a591499fbf7ed)`() const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_class_regex_iterator_1aa25ddc276c2fcdaa151974da64d717b8)`() const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`canUseValue`](#classrexgen_1_1_class_regex_iterator_1a0efb156682be30fd85ad09dee8ba73a5)`() const` 

#### `public inline std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_class_regex_iterator_1a96d8d9f201e731f5efbceaf2661a90c4)`() const` 

#### `public inline void `[`setCurrentState`](#classrexgen_1_1_class_regex_iterator_1a90e36aa2d1f5a1e344350163c8d38c7e)`(const std::shared_ptr< SerializableState > & s)` 

#### `private signed int `[`current`](#classrexgen_1_1_class_regex_iterator_1aff1a477f0e0dad7fe44ef069e61bbe43) 

#### `private int `[`characters_count`](#classrexgen_1_1_class_regex_iterator_1aab27ad37bbb32f13229951861dbc186a) 

#### `private SimpleString `[`characters`](#classrexgen_1_1_class_regex_iterator_1a4f718f9914d9e6689d33be7afbf04808) 

#### `private vector< std::string::size_type > `[`indices`](#classrexgen_1_1_class_regex_iterator_1a55855dbd631cc6b77880061231645697) 

#### `private vector< std::string::size_type > `[`lengths`](#classrexgen_1_1_class_regex_iterator_1a79c1926e759f777e39026d38dbc26d90) 

## class `rexgen::CompoundRegex` 

```
class rexgen::CompoundRegex
  : public rexgen::RegexContainer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`prependRegex`](#classrexgen_1_1_compound_regex_1a1f4cf469fb907cb75089ba017ee91833)`(const std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` | 
`public void `[`appendRegex`](#classrexgen_1_1_compound_regex_1ac284905613375fa66163d93f1b22d33d)`(const std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` | 
`public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_compound_regex_1a94fe114858729e04ed7372400bbc34d2)`() const` | 
`public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_compound_regex_1ae35ad84e84054f4474e22cc53c2fa599)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_compound_regex_1a7d13c93bee43f9ffa697f68294982340)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 

### Members

#### `public void `[`prependRegex`](#classrexgen_1_1_compound_regex_1a1f4cf469fb907cb75089ba017ee91833)`(const std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` 

#### `public void `[`appendRegex`](#classrexgen_1_1_compound_regex_1ac284905613375fa66163d93f1b22d33d)`(const std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` 

#### `public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_compound_regex_1a94fe114858729e04ed7372400bbc34d2)`() const` 

#### `public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_compound_regex_1ae35ad84e84054f4474e22cc53c2fa599)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_compound_regex_1a7d13c93bee43f9ffa697f68294982340)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

## class `rexgen::CompoundRegexIterator` 

```
class rexgen::CompoundRegexIterator
  : public IteratorContainer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`CompoundRegexIterator`](#classrexgen_1_1_compound_regex_iterator_1a14b0ccb5ee328972356c0f768c88af5d)`()` | 
`public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_compound_regex_iterator_1a3e2caacfa6076775159b075f7d268dad)`()` | 
`public void `[`value`](#classrexgen_1_1_compound_regex_iterator_1a985b04b33e3ad8d0ce60a5433fce2948)`(SimpleString * dst) const` | 
`public std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_compound_regex_iterator_1a297536a36fbdde7460d7bcd97b7f80f8)`() const` | 
`public void `[`setCurrentState`](#classrexgen_1_1_compound_regex_iterator_1a4e5eba05881f6b71aa8bc6dddcac903d)`(const std::shared_ptr< SerializableState > & state)` | 

### Members

#### `public  explicit `[`CompoundRegexIterator`](#classrexgen_1_1_compound_regex_iterator_1a14b0ccb5ee328972356c0f768c88af5d)`()` 

#### `public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_compound_regex_iterator_1a3e2caacfa6076775159b075f7d268dad)`()` 

#### `public void `[`value`](#classrexgen_1_1_compound_regex_iterator_1a985b04b33e3ad8d0ce60a5433fce2948)`(SimpleString * dst) const` 

#### `public std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_compound_regex_iterator_1a297536a36fbdde7460d7bcd97b7f80f8)`() const` 

#### `public void `[`setCurrentState`](#classrexgen_1_1_compound_regex_iterator_1a4e5eba05881f6b71aa8bc6dddcac903d)`(const std::shared_ptr< SerializableState > & state)` 

## class `rexgen::FastIteratorPermuter` 

```
class rexgen::FastIteratorPermuter
  : public Iterator
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`FastIteratorPermuter`](#classrexgen_1_1_fast_iterator_permuter_1ade68d44909a7383f5bc4d513de576a56)`(unsigned int count)` | 
`public inline void `[`value`](#classrexgen_1_1_fast_iterator_permuter_1ad467a5dc9d9ee34a8888b472535e8522)`(SimpleString * dst) const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_fast_iterator_permuter_1a79d96e696dde2adafabdd8b29a50773f)`()` | 
`public inline void `[`updateAttributes`](#classrexgen_1_1_fast_iterator_permuter_1a0aee9b2ccf4544e6a2d488477d18fb96)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & iterState)` | 
`public inline void `[`updateReferences`](#classrexgen_1_1_fast_iterator_permuter_1a24353495a889a6ad75c73cfc488b119b)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & iterState)` | 
`private std::vector< ITERATOR > `[`iterators`](#classrexgen_1_1_fast_iterator_permuter_1a98bfbe1ab3e7df7db7869777f6998495) | 

### Members

#### `public inline  `[`FastIteratorPermuter`](#classrexgen_1_1_fast_iterator_permuter_1ade68d44909a7383f5bc4d513de576a56)`(unsigned int count)` 

#### `public inline void `[`value`](#classrexgen_1_1_fast_iterator_permuter_1ad467a5dc9d9ee34a8888b472535e8522)`(SimpleString * dst) const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_fast_iterator_permuter_1a79d96e696dde2adafabdd8b29a50773f)`()` 

#### `public inline void `[`updateAttributes`](#classrexgen_1_1_fast_iterator_permuter_1a0aee9b2ccf4544e6a2d488477d18fb96)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & iterState)` 

#### `public inline void `[`updateReferences`](#classrexgen_1_1_fast_iterator_permuter_1a24353495a889a6ad75c73cfc488b119b)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & iterState)` 

#### `private std::vector< ITERATOR > `[`iterators`](#classrexgen_1_1_fast_iterator_permuter_1a98bfbe1ab3e7df7db7869777f6998495) 

## class `rexgen::GroupReference` 

```
class rexgen::GroupReference
  : public rexgen::Regex
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`GroupReference`](#classrexgen_1_1_group_reference_1a4df4746269db482195595ce59999e568)`(int _groupId)` | 
`public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_group_reference_1a827460af82cd034568e9cbb9709306c3)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_group_reference_1a038f609cacd826d9ecb6b689a0751833)`() const` | 
`public inline virtual int `[`getGroupId`](#classrexgen_1_1_group_reference_1af0525544871d6e3a4bca47e2047c08c0)`() const` | 
`public inline const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & `[`getRegex`](#classrexgen_1_1_group_reference_1a8e872cc2cc97297d4b29f6d280e78c86)`() const` | 
`public inline void `[`setRegex`](#classrexgen_1_1_group_reference_1a08d5ab04842c27f9fd862961173947b1)`(const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & re)` | 
`public inline std::uint64_t `[`size`](#classrexgen_1_1_group_reference_1ad7c68181619e541a7b19fd6327a83bcc)`() const` | 
`private const int `[`groupId`](#classrexgen_1_1_group_reference_1a78d82f4fff86bc2f9d6348f80933d14a) | 
`private std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`groupRef`](#classrexgen_1_1_group_reference_1af2affee73a12ac025e4613c685840e45) | 

### Members

#### `public inline  explicit `[`GroupReference`](#classrexgen_1_1_group_reference_1a4df4746269db482195595ce59999e568)`(int _groupId)` 

#### `public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_group_reference_1a827460af82cd034568e9cbb9709306c3)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_group_reference_1a038f609cacd826d9ecb6b689a0751833)`() const` 

#### `public inline virtual int `[`getGroupId`](#classrexgen_1_1_group_reference_1af0525544871d6e3a4bca47e2047c08c0)`() const` 

#### `public inline const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & `[`getRegex`](#classrexgen_1_1_group_reference_1a8e872cc2cc97297d4b29f6d280e78c86)`() const` 

#### `public inline void `[`setRegex`](#classrexgen_1_1_group_reference_1a08d5ab04842c27f9fd862961173947b1)`(const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & re)` 

#### `public inline std::uint64_t `[`size`](#classrexgen_1_1_group_reference_1ad7c68181619e541a7b19fd6327a83bcc)`() const` 

#### `private const int `[`groupId`](#classrexgen_1_1_group_reference_1a78d82f4fff86bc2f9d6348f80933d14a) 

#### `private std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`groupRef`](#classrexgen_1_1_group_reference_1af2affee73a12ac025e4613c685840e45) 

## class `rexgen::GroupReferenceIterator` 

```
class rexgen::GroupReferenceIterator
  : public IteratorContainer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`GroupReferenceIterator`](#classrexgen_1_1_group_reference_iterator_1a2ffd297b09646bb1fa6dfefcfea66ddc)`(int group)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_group_reference_iterator_1a50c9abe901f346f9b1d5d9ec8ba6f6a7)`() const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_group_reference_iterator_1a243f9b1d88ca47e3d0ab2bbc65a6f31d)`()` | 
`public inline void `[`value`](#classrexgen_1_1_group_reference_iterator_1a0ae1fdb3ce03609af849007b4105b701)`(SimpleString * dst) const` | 
`public void `[`updateReferences`](#classrexgen_1_1_group_reference_iterator_1a4b567cd1ca63f40a38d1e3ad5b9bb3bd)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & iterState)` | 
`private NullIterator `[`null_iter`](#classrexgen_1_1_group_reference_iterator_1ad86ef10a25b1fb2f36d238e8320fa484) | 
`private int `[`groupId`](#classrexgen_1_1_group_reference_iterator_1a27454324754cc4f2614cb364696d9c1a) | 
`private std::reference_wrapper< Iterator > `[`groupRef`](#classrexgen_1_1_group_reference_iterator_1ada133a267025a9683de710150597944a) | 

### Members

#### `public inline  `[`GroupReferenceIterator`](#classrexgen_1_1_group_reference_iterator_1a2ffd297b09646bb1fa6dfefcfea66ddc)`(int group)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_group_reference_iterator_1a50c9abe901f346f9b1d5d9ec8ba6f6a7)`() const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_group_reference_iterator_1a243f9b1d88ca47e3d0ab2bbc65a6f31d)`()` 

#### `public inline void `[`value`](#classrexgen_1_1_group_reference_iterator_1a0ae1fdb3ce03609af849007b4105b701)`(SimpleString * dst) const` 

#### `public void `[`updateReferences`](#classrexgen_1_1_group_reference_iterator_1a4b567cd1ca63f40a38d1e3ad5b9bb3bd)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & iterState)` 

#### `private NullIterator `[`null_iter`](#classrexgen_1_1_group_reference_iterator_1ad86ef10a25b1fb2f36d238e8320fa484) 

#### `private int `[`groupId`](#classrexgen_1_1_group_reference_iterator_1a27454324754cc4f2614cb364696d9c1a) 

#### `private std::reference_wrapper< Iterator > `[`groupRef`](#classrexgen_1_1_group_reference_iterator_1ada133a267025a9683de710150597944a) 

## class `rexgen::IteratorPermuter` 

```
class rexgen::IteratorPermuter
  : public IteratorContainer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`value`](#classrexgen_1_1_iterator_permuter_1a7f3fc77e7feab714fb121947e257c37e)`(SimpleString * dst) const` | 
`public  `[`IteratorPermuter`](#classrexgen_1_1_iterator_permuter_1a68b4bbaed9d7fa8b27ee31bf18bbcc66)`(const `[`Regex`](#classrexgen_1_1_regex)` & re,`[`IteratorState`](#classrexgen_1_1_iterator_state)` & is,unsigned int min,unsigned int max)` | 
`public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_iterator_permuter_1acf600fc7bd32244b67e6b5898401c4f0)`()` | 
`public void `[`init`](#classrexgen_1_1_iterator_permuter_1a792e4e891d635d4cef9060566475d293)`()` | 
`private const unsigned int `[`min_occurs`](#classrexgen_1_1_iterator_permuter_1a8e6e4ace7d4a9f882a51d4a76a30165f) | 
`private const unsigned int `[`max_occurs`](#classrexgen_1_1_iterator_permuter_1a92a0c062e1d32f4a0d54cefe000db880) | 
`private unsigned int `[`current`](#classrexgen_1_1_iterator_permuter_1af50ee803b6d32b788005150416c860c8) | 
`private unsigned int `[`occurs`](#classrexgen_1_1_iterator_permuter_1a1afeb9c7132bb1746770da1f219764ba) | 

### Members

#### `public void `[`value`](#classrexgen_1_1_iterator_permuter_1a7f3fc77e7feab714fb121947e257c37e)`(SimpleString * dst) const` 

#### `public  `[`IteratorPermuter`](#classrexgen_1_1_iterator_permuter_1a68b4bbaed9d7fa8b27ee31bf18bbcc66)`(const `[`Regex`](#classrexgen_1_1_regex)` & re,`[`IteratorState`](#classrexgen_1_1_iterator_state)` & is,unsigned int min,unsigned int max)` 

#### `public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_iterator_permuter_1acf600fc7bd32244b67e6b5898401c4f0)`()` 

#### `public void `[`init`](#classrexgen_1_1_iterator_permuter_1a792e4e891d635d4cef9060566475d293)`()` 

#### `private const unsigned int `[`min_occurs`](#classrexgen_1_1_iterator_permuter_1a8e6e4ace7d4a9f882a51d4a76a30165f) 

#### `private const unsigned int `[`max_occurs`](#classrexgen_1_1_iterator_permuter_1a92a0c062e1d32f4a0d54cefe000db880) 

#### `private unsigned int `[`current`](#classrexgen_1_1_iterator_permuter_1af50ee803b6d32b788005150416c860c8) 

#### `private unsigned int `[`occurs`](#classrexgen_1_1_iterator_permuter_1a1afeb9c7132bb1746770da1f219764ba) 

## class `rexgen::IteratorState` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`IteratorState`](#classrexgen_1_1_iterator_state_1a121cf83c973c797bdbf85e2091b23a58)`()` | 
`public  `[`IteratorState`](#classrexgen_1_1_iterator_state_1a2acbe6031bf499863aefa0f8c1906d9f)`(const `[`IteratorState`](#classrexgen_1_1_iterator_state)` &) = delete` | 
`public  `[`IteratorState`](#classrexgen_1_1_iterator_state_1a5dd6ee9ecdfd13fa1e8bd6cd7e224c0f)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &&) = delete` | 
`public `[`IteratorState`](#classrexgen_1_1_iterator_state)` & `[`operator=`](#classrexgen_1_1_iterator_state_1a787837411fcef1ecdd11934436930700)`(const `[`IteratorState`](#classrexgen_1_1_iterator_state)` &) = delete` | 
`public `[`IteratorState`](#classrexgen_1_1_iterator_state)` & `[`operator=`](#classrexgen_1_1_iterator_state_1a9e477729d426710efc924fe168d9a266)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &&) = delete` | 
`public inline void `[`registerIterator`](#classrexgen_1_1_iterator_state_1a66d056398d427a600a0bd47a2b7a7ee2)`(int id,std::reference_wrapper< Iterator > iterator)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasId`](#classrexgen_1_1_iterator_state_1a8f2386ed14a146b1a1f52b0e33364866)`(int id) const` | 
`public inline std::reference_wrapper< Iterator > `[`operator[]`](#classrexgen_1_1_iterator_state_1a03b8c9f67af28e1655a37129da38a40d)`(int id) const` | 
`public inline void `[`setStreamIterator`](#classrexgen_1_1_iterator_state_1a8e36270b2de89e34ab045bf8a0ee897d)`(std::unique_ptr< `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator)` > & iter)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasStreamIterator`](#classrexgen_1_1_iterator_state_1ab40cd1f6748afb36e423fa271600097e)`() const` | 
`public inline std::reference_wrapper< `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator)` > `[`getStreamIterator`](#classrexgen_1_1_iterator_state_1aa0eaee9239520cd15a0a6085e670eb3a)`() const` | 
`private std::map< int, std::reference_wrapper< Iterator > > `[`groupIterators`](#classrexgen_1_1_iterator_state_1a62bd2d630e9c2273304b555c57aeaca6) | 
`private mutable std::unique_ptr< `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator)` > `[`streamIterator`](#classrexgen_1_1_iterator_state_1ae56449b14ddc4143d4b84a38f41e87d4) | 

### Members

#### `public inline  explicit `[`IteratorState`](#classrexgen_1_1_iterator_state_1a121cf83c973c797bdbf85e2091b23a58)`()` 

#### `public  `[`IteratorState`](#classrexgen_1_1_iterator_state_1a2acbe6031bf499863aefa0f8c1906d9f)`(const `[`IteratorState`](#classrexgen_1_1_iterator_state)` &) = delete` 

#### `public  `[`IteratorState`](#classrexgen_1_1_iterator_state_1a5dd6ee9ecdfd13fa1e8bd6cd7e224c0f)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &&) = delete` 

#### `public `[`IteratorState`](#classrexgen_1_1_iterator_state)` & `[`operator=`](#classrexgen_1_1_iterator_state_1a787837411fcef1ecdd11934436930700)`(const `[`IteratorState`](#classrexgen_1_1_iterator_state)` &) = delete` 

#### `public `[`IteratorState`](#classrexgen_1_1_iterator_state)` & `[`operator=`](#classrexgen_1_1_iterator_state_1a9e477729d426710efc924fe168d9a266)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &&) = delete` 

#### `public inline void `[`registerIterator`](#classrexgen_1_1_iterator_state_1a66d056398d427a600a0bd47a2b7a7ee2)`(int id,std::reference_wrapper< Iterator > iterator)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasId`](#classrexgen_1_1_iterator_state_1a8f2386ed14a146b1a1f52b0e33364866)`(int id) const` 

#### `public inline std::reference_wrapper< Iterator > `[`operator[]`](#classrexgen_1_1_iterator_state_1a03b8c9f67af28e1655a37129da38a40d)`(int id) const` 

#### `public inline void `[`setStreamIterator`](#classrexgen_1_1_iterator_state_1a8e36270b2de89e34ab045bf8a0ee897d)`(std::unique_ptr< `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator)` > & iter)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasStreamIterator`](#classrexgen_1_1_iterator_state_1ab40cd1f6748afb36e423fa271600097e)`() const` 

#### `public inline std::reference_wrapper< `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator)` > `[`getStreamIterator`](#classrexgen_1_1_iterator_state_1aa0eaee9239520cd15a0a6085e670eb3a)`() const` 

#### `private std::map< int, std::reference_wrapper< Iterator > > `[`groupIterators`](#classrexgen_1_1_iterator_state_1a62bd2d630e9c2273304b555c57aeaca6) 

#### `private mutable std::unique_ptr< `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator)` > `[`streamIterator`](#classrexgen_1_1_iterator_state_1ae56449b14ddc4143d4b84a38f41e87d4) 

## class `rexgen::Quantifier` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public unsigned int `[`min`](#classrexgen_1_1_quantifier_1a3d6717ee72f5707529ba26e2d58b411a) | 
`public unsigned int `[`max`](#classrexgen_1_1_quantifier_1ad1243810d0ecf0edf3a59d74de480358) | 
`public inline  `[`Quantifier`](#classrexgen_1_1_quantifier_1a4f267772c317299a521baf4758190ac3)`()` | 
`public inline  `[`Quantifier`](#classrexgen_1_1_quantifier_1a02321cd2ee95d05c24ae34d98f60a056)`(unsigned int _min,unsigned int _max)` | 
`public inline  `[`Quantifier`](#classrexgen_1_1_quantifier_1a2229c87a9f54cddb8243fd414d53bee2)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & other)` | 
`public inline virtual  `[`~Quantifier`](#classrexgen_1_1_quantifier_1a0aca01d3efad30cd5ce84690de62ade7)`()` | 
`public inline virtual `[`Quantifier`](#classrexgen_1_1_quantifier)` & `[`operator=`](#classrexgen_1_1_quantifier_1a778c76dddabce063fb3872752cc70097)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & other)` | 
`public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`operator==`](#classrexgen_1_1_quantifier_1a8280ea46d67d1b56f54dcf9c50cf2247)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & other) const` | 
`public inline unsigned int `[`getMin`](#classrexgen_1_1_quantifier_1a777998bd7ccc2f43b057f5db38b400c9)`() const` | 
`public inline unsigned int `[`getMax`](#classrexgen_1_1_quantifier_1a324aa30b13ca224900f6392912627720)`() const` | 
`public inline void `[`setMin`](#classrexgen_1_1_quantifier_1a131ea39d572227709f0842ce9704effc)`(unsigned _min)` | 
`public inline void `[`setMax`](#classrexgen_1_1_quantifier_1a672fdb376f0f346fafeea511d78d761c)`(unsigned _max)` | 

### Members

#### `public unsigned int `[`min`](#classrexgen_1_1_quantifier_1a3d6717ee72f5707529ba26e2d58b411a) 

#### `public unsigned int `[`max`](#classrexgen_1_1_quantifier_1ad1243810d0ecf0edf3a59d74de480358) 

#### `public inline  `[`Quantifier`](#classrexgen_1_1_quantifier_1a4f267772c317299a521baf4758190ac3)`()` 

#### `public inline  `[`Quantifier`](#classrexgen_1_1_quantifier_1a02321cd2ee95d05c24ae34d98f60a056)`(unsigned int _min,unsigned int _max)` 

#### `public inline  `[`Quantifier`](#classrexgen_1_1_quantifier_1a2229c87a9f54cddb8243fd414d53bee2)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & other)` 

#### `public inline virtual  `[`~Quantifier`](#classrexgen_1_1_quantifier_1a0aca01d3efad30cd5ce84690de62ade7)`()` 

#### `public inline virtual `[`Quantifier`](#classrexgen_1_1_quantifier)` & `[`operator=`](#classrexgen_1_1_quantifier_1a778c76dddabce063fb3872752cc70097)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & other)` 

#### `public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`operator==`](#classrexgen_1_1_quantifier_1a8280ea46d67d1b56f54dcf9c50cf2247)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & other) const` 

#### `public inline unsigned int `[`getMin`](#classrexgen_1_1_quantifier_1a777998bd7ccc2f43b057f5db38b400c9)`() const` 

#### `public inline unsigned int `[`getMax`](#classrexgen_1_1_quantifier_1a324aa30b13ca224900f6392912627720)`() const` 

#### `public inline void `[`setMin`](#classrexgen_1_1_quantifier_1a131ea39d572227709f0842ce9704effc)`(unsigned _min)` 

#### `public inline void `[`setMax`](#classrexgen_1_1_quantifier_1a672fdb376f0f346fafeea511d78d761c)`(unsigned _max)` 

## class `rexgen::RangeIterator` 

```
class rexgen::RangeIterator
  : public Iterator
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`RangeIterator`](#classrexgen_1_1_range_iterator_1ae025431d97654a41e525fee04973ec13)`()` | 
`public inline void `[`value`](#classrexgen_1_1_range_iterator_1a47587ee8f2fd2ec5a8fd82453d7f43d4)`(SimpleString * dst) const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_range_iterator_1af33042a3127e682459c423244505ae68)`()` | 
`public inline void `[`updateReferences`](#classrexgen_1_1_range_iterator_1a5e8f63b1344c7531e0607fec045b2e0a)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline void `[`updateAttributes`](#classrexgen_1_1_range_iterator_1af2c82f734ca2470014a1a69735dce446)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`private char `[`current`](#classrexgen_1_1_range_iterator_1a09214f9c94a7ee00c760d08621c3b17a) | 
`private const char `[`minimum`](#classrexgen_1_1_range_iterator_1a56e87af86aeb06ca043a2747054bf0bb) | 
`private const char `[`maximum`](#classrexgen_1_1_range_iterator_1a82cd61e6e3eaf6c77ecb133797bd41c8) | 

### Members

#### `public inline  explicit `[`RangeIterator`](#classrexgen_1_1_range_iterator_1ae025431d97654a41e525fee04973ec13)`()` 

#### `public inline void `[`value`](#classrexgen_1_1_range_iterator_1a47587ee8f2fd2ec5a8fd82453d7f43d4)`(SimpleString * dst) const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_range_iterator_1af33042a3127e682459c423244505ae68)`()` 

#### `public inline void `[`updateReferences`](#classrexgen_1_1_range_iterator_1a5e8f63b1344c7531e0607fec045b2e0a)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline void `[`updateAttributes`](#classrexgen_1_1_range_iterator_1af2c82f734ca2470014a1a69735dce446)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `private char `[`current`](#classrexgen_1_1_range_iterator_1a09214f9c94a7ee00c760d08621c3b17a) 

#### `private const char `[`minimum`](#classrexgen_1_1_range_iterator_1a56e87af86aeb06ca043a2747054bf0bb) 

#### `private const char `[`maximum`](#classrexgen_1_1_range_iterator_1a82cd61e6e3eaf6c77ecb133797bd41c8) 

## class `rexgen::Regex` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`Regex`](#classrexgen_1_1_regex_1aa2b7b37ad5a4184d7eddf6179677ad92)`()` | 
`public inline virtual  `[`~Regex`](#classrexgen_1_1_regex_1a8c62e5b55908518cf0da7c9868cfe1b7)`()` | 
`public inline unsigned int `[`getMinOccurs`](#classrexgen_1_1_regex_1af4b2de330cc6ad54f969152589b49348)`() const` | 
`public inline unsigned int `[`getMaxOccurs`](#classrexgen_1_1_regex_1a89db2f6d20d4b6938a8146db1f687278)`() const` | 
`public inline void `[`setMinOccurs`](#classrexgen_1_1_regex_1ad852647532c0a907d4c8e72efb351938)`(unsigned int _min)` | 
`public inline void `[`setMaxOccurs`](#classrexgen_1_1_regex_1aba73061b27efa491e1a3882addbdcd3b)`(unsigned int _max)` | 
`public inline void `[`setQuantifier`](#classrexgen_1_1_regex_1a53576c32fb0444ad2aa5c242ac24e100)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & q)` | 
`public `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_regex_1ac8dcecf6c15b6765a459750bff421d84)`() const` | 
`public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_regex_1ad4d96086f081f2a281dc14f27bb9475d)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_regex_1aca8d87f71804f399d7340fc7daaed01a)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public inline int `[`getId`](#classrexgen_1_1_regex_1aad56bbdcf3073a09f0770d8486f004e7)`() const` | 
`public inline virtual int `[`getGroupId`](#classrexgen_1_1_regex_1a5594535172f6ac3fa5f34a36c3bd5a0c)`() const` | 
`public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`usesCallback`](#classrexgen_1_1_regex_1a3631fd5406c4e82d9b01f50a65b70aac)`() const` | 
`protected inline virtual int `[`createId`](#classrexgen_1_1_regex_1a13c2e8a32b4a1fae100d1891604700cb)`()` | 
`private `[`Quantifier`](#classrexgen_1_1_quantifier)` `[`quantifier`](#classrexgen_1_1_regex_1ac49ec833f8c4675acd9c24023adf7759) | 
`private int `[`id`](#classrexgen_1_1_regex_1aa8ea17fb0b0d6160699f6d36808c6039) | 

### Members

#### `public inline  `[`Regex`](#classrexgen_1_1_regex_1aa2b7b37ad5a4184d7eddf6179677ad92)`()` 

#### `public inline virtual  `[`~Regex`](#classrexgen_1_1_regex_1a8c62e5b55908518cf0da7c9868cfe1b7)`()` 

#### `public inline unsigned int `[`getMinOccurs`](#classrexgen_1_1_regex_1af4b2de330cc6ad54f969152589b49348)`() const` 

#### `public inline unsigned int `[`getMaxOccurs`](#classrexgen_1_1_regex_1a89db2f6d20d4b6938a8146db1f687278)`() const` 

#### `public inline void `[`setMinOccurs`](#classrexgen_1_1_regex_1ad852647532c0a907d4c8e72efb351938)`(unsigned int _min)` 

#### `public inline void `[`setMaxOccurs`](#classrexgen_1_1_regex_1aba73061b27efa491e1a3882addbdcd3b)`(unsigned int _max)` 

#### `public inline void `[`setQuantifier`](#classrexgen_1_1_regex_1a53576c32fb0444ad2aa5c242ac24e100)`(const `[`Quantifier`](#classrexgen_1_1_quantifier)` & q)` 

#### `public `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_regex_1ac8dcecf6c15b6765a459750bff421d84)`() const` 

#### `public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_regex_1ad4d96086f081f2a281dc14f27bb9475d)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_regex_1aca8d87f71804f399d7340fc7daaed01a)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public inline int `[`getId`](#classrexgen_1_1_regex_1aad56bbdcf3073a09f0770d8486f004e7)`() const` 

#### `public inline virtual int `[`getGroupId`](#classrexgen_1_1_regex_1a5594535172f6ac3fa5f34a36c3bd5a0c)`() const` 

#### `public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`usesCallback`](#classrexgen_1_1_regex_1a3631fd5406c4e82d9b01f50a65b70aac)`() const` 

#### `protected inline virtual int `[`createId`](#classrexgen_1_1_regex_1a13c2e8a32b4a1fae100d1891604700cb)`()` 

#### `private `[`Quantifier`](#classrexgen_1_1_quantifier)` `[`quantifier`](#classrexgen_1_1_regex_1ac49ec833f8c4675acd9c24023adf7759) 

#### `private int `[`id`](#classrexgen_1_1_regex_1aa8ea17fb0b0d6160699f6d36808c6039) 

## class `rexgen::RegexAlternatives` 

```
class rexgen::RegexAlternatives
  : public rexgen::RegexContainer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`RegexAlternatives`](#classrexgen_1_1_regex_alternatives_1a6277b2be3c3497e6e9125a9852bce607)`()` | 
`public inline void `[`addRegex`](#classrexgen_1_1_regex_alternatives_1a2a34190feb0afb05c377a05018a5ed82)`(std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` | 
`public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_regex_alternatives_1a4d9790d76a12f4597636583e4b865ff6)`() const` | 
`public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_regex_alternatives_1a9ea00630d27e73a387f0b28c2b837d99)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_regex_alternatives_1acca7ec3f433493ffc66d7d36592a1e01)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public inline virtual int `[`getGroupId`](#classrexgen_1_1_regex_alternatives_1ad36136fa496a9483c803efd7c679d85a)`() const` | 
`public inline void `[`setGroupId`](#classrexgen_1_1_regex_alternatives_1aedf24a60e0eb62abc989bfdd1bf4e440)`(int _id)` | 
`public inline void `[`setGroupOptions`](#classrexgen_1_1_regex_alternatives_1a88eb11fbbe51026ee61fa84a46227d0d)`(const `[`t_group_options`](#structrexgen_1_1t__group__options)` & opts)` | 
`private int `[`groupId`](#classrexgen_1_1_regex_alternatives_1a55e4c27f4f114a0e157f697f38c18e62) | 
`private int `[`handle_case`](#classrexgen_1_1_regex_alternatives_1a9db06f3c4a3531b0a9e1751ed274801d) | 

### Members

#### `public inline  `[`RegexAlternatives`](#classrexgen_1_1_regex_alternatives_1a6277b2be3c3497e6e9125a9852bce607)`()` 

#### `public inline void `[`addRegex`](#classrexgen_1_1_regex_alternatives_1a2a34190feb0afb05c377a05018a5ed82)`(std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` 

#### `public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_regex_alternatives_1a4d9790d76a12f4597636583e4b865ff6)`() const` 

#### `public virtual std::unique_ptr< Iterator > `[`iterator`](#classrexgen_1_1_regex_alternatives_1a9ea00630d27e73a387f0b28c2b837d99)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_regex_alternatives_1acca7ec3f433493ffc66d7d36592a1e01)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public inline virtual int `[`getGroupId`](#classrexgen_1_1_regex_alternatives_1ad36136fa496a9483c803efd7c679d85a)`() const` 

#### `public inline void `[`setGroupId`](#classrexgen_1_1_regex_alternatives_1aedf24a60e0eb62abc989bfdd1bf4e440)`(int _id)` 

#### `public inline void `[`setGroupOptions`](#classrexgen_1_1_regex_alternatives_1a88eb11fbbe51026ee61fa84a46227d0d)`(const `[`t_group_options`](#structrexgen_1_1t__group__options)` & opts)` 

#### `private int `[`groupId`](#classrexgen_1_1_regex_alternatives_1a55e4c27f4f114a0e157f697f38c18e62) 

#### `private int `[`handle_case`](#classrexgen_1_1_regex_alternatives_1a9db06f3c4a3531b0a9e1751ed274801d) 

## class `rexgen::RegexAlternativesIterator` 

```
class rexgen::RegexAlternativesIterator
  : public IteratorContainer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  explicit `[`RegexAlternativesIterator`](#classrexgen_1_1_regex_alternatives_iterator_1ae36dcdae7f2459ffb5380a8b953bce9c)`()` | 
`public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_regex_alternatives_iterator_1a8899d96ca03f5be4b9bfbfcf379c8872)`()` | 
`public inline void `[`value`](#classrexgen_1_1_regex_alternatives_iterator_1a3afb695cd489fb38f35db29344b91ab1)`(SimpleString * dst) const` | 
`public void `[`addChild`](#classrexgen_1_1_regex_alternatives_iterator_1a7ce99f7b8ba0626c118b34326ba13ca0)`(std::unique_ptr< Iterator > && re)` | 
`public std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_regex_alternatives_iterator_1a1885b4120da83fd24476d4cb3ce45a25)`() const` | 
`public void `[`setCurrentState`](#classrexgen_1_1_regex_alternatives_iterator_1a5cc0dc34a9c85dfb855ae8d3da40b162)`(const std::shared_ptr< SerializableState > & state)` | 
`private `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`canUseValue`](#classrexgen_1_1_regex_alternatives_iterator_1ad69713fcb6dd04421b28c3a21612aace)`() const` | 

### Members

#### `public  explicit `[`RegexAlternativesIterator`](#classrexgen_1_1_regex_alternatives_iterator_1ae36dcdae7f2459ffb5380a8b953bce9c)`()` 

#### `public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_regex_alternatives_iterator_1a8899d96ca03f5be4b9bfbfcf379c8872)`()` 

#### `public inline void `[`value`](#classrexgen_1_1_regex_alternatives_iterator_1a3afb695cd489fb38f35db29344b91ab1)`(SimpleString * dst) const` 

#### `public void `[`addChild`](#classrexgen_1_1_regex_alternatives_iterator_1a7ce99f7b8ba0626c118b34326ba13ca0)`(std::unique_ptr< Iterator > && re)` 

#### `public std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_regex_alternatives_iterator_1a1885b4120da83fd24476d4cb3ce45a25)`() const` 

#### `public void `[`setCurrentState`](#classrexgen_1_1_regex_alternatives_iterator_1a5cc0dc34a9c85dfb855ae8d3da40b162)`(const std::shared_ptr< SerializableState > & state)` 

#### `private `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`canUseValue`](#classrexgen_1_1_regex_alternatives_iterator_1ad69713fcb6dd04421b28c3a21612aace)`() const` 

## class `rexgen::RegexContainer` 

```
class rexgen::RegexContainer
  : public rexgen::Regex
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`usesCallback`](#classrexgen_1_1_regex_container_1a30ad38bd19111bd5b17a4a77d8aa54d9)`() const` | 
`protected std::deque< std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > `[`regexObjects`](#classrexgen_1_1_regex_container_1a79cdaa2132f01e99a178ae20b3b7673e) | 
`protected inline std::deque< std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > & `[`getChildren`](#classrexgen_1_1_regex_container_1a7869830d8bc14036250421ad59d07606)`()` | 

### Members

#### `public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`usesCallback`](#classrexgen_1_1_regex_container_1a30ad38bd19111bd5b17a4a77d8aa54d9)`() const` 

#### `protected std::deque< std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > `[`regexObjects`](#classrexgen_1_1_regex_container_1a79cdaa2132f01e99a178ae20b3b7673e) 

#### `protected inline std::deque< std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > & `[`getChildren`](#classrexgen_1_1_regex_container_1a7869830d8bc14036250421ad59d07606)`()` 

## class `rexgen::RexgenFlexLexer` 

```
class rexgen::RexgenFlexLexer
  : public yyFlexLexer
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`RexgenFlexLexer`](#classrexgen_1_1_rexgen_flex_lexer_1a461946565a79e58e26ed3459ba016d2c)`(const std::string & input)` | 
`public RexgenParser::symbol_type `[`rexgen_lex`](#classrexgen_1_1_rexgen_flex_lexer_1a2619bf65ec57dba41c466bd52f7e0785)`(`[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver)` & driver)` | 
`public int `[`LexerInput`](#classrexgen_1_1_rexgen_flex_lexer_1a870bb3d3a04bf326809f967a780c2af7)`(char * buf,int max_size)` | 
`public rexgen::RexgenParser::symbol_type `[`beginGroupWithOptions`](#classrexgen_1_1_rexgen_flex_lexer_1a8a0d5285a0de12c23887c402952099be)`(`[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver)` & driver) const` | 
`public rexgen::RexgenParser::symbol_type `[`beginGroup`](#classrexgen_1_1_rexgen_flex_lexer_1a5c85946d63532feb96188456e4f51c20)`(`[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver)` & driver) const` | 
`private std::string `[`content`](#classrexgen_1_1_rexgen_flex_lexer_1ad20cfcc9b616f56917c4f0fe1d0e43a0) | 
`private std::string::const_iterator `[`content_ptr`](#classrexgen_1_1_rexgen_flex_lexer_1aa766316825f95c30387a41f2cd560811) | 
`private std::wstring `[`wcontent`](#classrexgen_1_1_rexgen_flex_lexer_1a95597b563e7486f8a1fcc91e7a8a7043) | 
`private std::wstring::const_iterator `[`wcontent_ptr`](#classrexgen_1_1_rexgen_flex_lexer_1adff6407f68394c8a6327d93dfe27ca7a) | 
`public static char `[`hex2bin`](#classrexgen_1_1_rexgen_flex_lexer_1ae0a6bc0bb2d74db3e3ad81479e364f1f)`(const char c)` | 
`public static char `[`parseAnsiChar`](#classrexgen_1_1_rexgen_flex_lexer_1a9431098515257fdae9777779390629bf)`(const char * text)` | 
`public static uint32_t `[`parseUnicodeChar`](#classrexgen_1_1_rexgen_flex_lexer_1a2da36217f9b63a5ad9acea5739f81881)`(const char * text)` | 
`public static void `[`UTF8_validate_second_byte`](#classrexgen_1_1_rexgen_flex_lexer_1a8385c0c7d461e81324463e33846cc9e4)`(const unsigned char c)` | 
`public static uint32_t `[`parseUTF8`](#classrexgen_1_1_rexgen_flex_lexer_1a02c5e35b88961e28912c8251b3c786cf)`(const unsigned char * text)` | 

### Members

#### `public  `[`RexgenFlexLexer`](#classrexgen_1_1_rexgen_flex_lexer_1a461946565a79e58e26ed3459ba016d2c)`(const std::string & input)` 

#### `public RexgenParser::symbol_type `[`rexgen_lex`](#classrexgen_1_1_rexgen_flex_lexer_1a2619bf65ec57dba41c466bd52f7e0785)`(`[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver)` & driver)` 

#### `public int `[`LexerInput`](#classrexgen_1_1_rexgen_flex_lexer_1a870bb3d3a04bf326809f967a780c2af7)`(char * buf,int max_size)` 

#### `public rexgen::RexgenParser::symbol_type `[`beginGroupWithOptions`](#classrexgen_1_1_rexgen_flex_lexer_1a8a0d5285a0de12c23887c402952099be)`(`[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver)` & driver) const` 

#### `public rexgen::RexgenParser::symbol_type `[`beginGroup`](#classrexgen_1_1_rexgen_flex_lexer_1a5c85946d63532feb96188456e4f51c20)`(`[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver)` & driver) const` 

#### `private std::string `[`content`](#classrexgen_1_1_rexgen_flex_lexer_1ad20cfcc9b616f56917c4f0fe1d0e43a0) 

#### `private std::string::const_iterator `[`content_ptr`](#classrexgen_1_1_rexgen_flex_lexer_1aa766316825f95c30387a41f2cd560811) 

#### `private std::wstring `[`wcontent`](#classrexgen_1_1_rexgen_flex_lexer_1a95597b563e7486f8a1fcc91e7a8a7043) 

#### `private std::wstring::const_iterator `[`wcontent_ptr`](#classrexgen_1_1_rexgen_flex_lexer_1adff6407f68394c8a6327d93dfe27ca7a) 

#### `public static char `[`hex2bin`](#classrexgen_1_1_rexgen_flex_lexer_1ae0a6bc0bb2d74db3e3ad81479e364f1f)`(const char c)` 

#### `public static char `[`parseAnsiChar`](#classrexgen_1_1_rexgen_flex_lexer_1a9431098515257fdae9777779390629bf)`(const char * text)` 

#### `public static uint32_t `[`parseUnicodeChar`](#classrexgen_1_1_rexgen_flex_lexer_1a2da36217f9b63a5ad9acea5739f81881)`(const char * text)` 

#### `public static void `[`UTF8_validate_second_byte`](#classrexgen_1_1_rexgen_flex_lexer_1a8385c0c7d461e81324463e33846cc9e4)`(const unsigned char c)` 

#### `public static uint32_t `[`parseUTF8`](#classrexgen_1_1_rexgen_flex_lexer_1a02c5e35b88961e28912c8251b3c786cf)`(const unsigned char * text)` 

## class `rexgen::RexgenOptions` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`ignore_case`](#classrexgen_1_1_rexgen_options_1ad70d667654410df25abeadc693358b4e) | 
`public `[`charset`](#defs_8h_1a2f3cb7be21014d7055143acd809e9ef1)` `[`encoding`](#classrexgen_1_1_rexgen_options_1a81a95d6eaa61ce865b4f3dd046d95c92) | 
`public std::FILE * `[`infile`](#classrexgen_1_1_rexgen_options_1ae1a5616024e98236f6db6a7e54ab71bd) | 
`public `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`stream_callback`](#classrexgen_1_1_rexgen_options_1aeaf8f9419694806fe2ca82709c50ee24) | 
`public void(* `[`parser_error`](#classrexgen_1_1_rexgen_options_1ade6850b48a8c5cb38ae60aefeee3ce82) | 
`public inline  `[`RexgenOptions`](#classrexgen_1_1_rexgen_options_1abd0b7df89294eb65f3b7538e2493f601)`()` | 

### Members

#### `public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`ignore_case`](#classrexgen_1_1_rexgen_options_1ad70d667654410df25abeadc693358b4e) 

#### `public `[`charset`](#defs_8h_1a2f3cb7be21014d7055143acd809e9ef1)` `[`encoding`](#classrexgen_1_1_rexgen_options_1a81a95d6eaa61ce865b4f3dd046d95c92) 

#### `public std::FILE * `[`infile`](#classrexgen_1_1_rexgen_options_1ae1a5616024e98236f6db6a7e54ab71bd) 

#### `public `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`stream_callback`](#classrexgen_1_1_rexgen_options_1aeaf8f9419694806fe2ca82709c50ee24) 

#### `public void(* `[`parser_error`](#classrexgen_1_1_rexgen_options_1ade6850b48a8c5cb38ae60aefeee3ce82) 

#### `public inline  `[`RexgenOptions`](#classrexgen_1_1_rexgen_options_1abd0b7df89294eb65f3b7538e2493f601)`()` 

## class `rexgen::RexgenParsingDriver` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver_1af1f73446ac2b7aae7da877d1bac0ff2f)`(const `[`RexgenOptions`](#classrexgen_1_1_rexgen_options)` & __options)` | 
`public inline int `[`nextGroupId`](#classrexgen_1_1_rexgen_parsing_driver_1aa45804ff10c026f2bfbd23ae1f01ce3f)`()` | 
`public std::shared_ptr< `[`rexgen::Regex`](#classrexgen_1_1_regex)` > `[`parse`](#classrexgen_1_1_rexgen_parsing_driver_1a09aeb99f2d916543ca3c354805daadbe)`(const std::string & regex)` | 
`public void `[`registerGroupReference`](#classrexgen_1_1_rexgen_parsing_driver_1ab17574ec184f293d73756b80e0b18d5a)`(std::shared_ptr< `[`GroupReference`](#classrexgen_1_1_group_reference)` > gr)` | 
`public const std::shared_ptr< std::set< std::shared_ptr< `[`GroupReference`](#classrexgen_1_1_group_reference)` > > > & `[`getGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a90e03815b1e31440aa7e0884bd9a05c2)`(int id) const` | 
`public void `[`registerGroup`](#classrexgen_1_1_rexgen_parsing_driver_1ad92a1e196b1abe2bb973829185803506)`(std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & re)` | 
`public const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & `[`getGroupRegex`](#classrexgen_1_1_rexgen_parsing_driver_1ac245d64519c3f2459e35da3097d1c0e7)`(int id) const` | 
`public const map< int, std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > & `[`getGroups`](#classrexgen_1_1_rexgen_parsing_driver_1a8faec385849c490650a444905a0e2513)`() const` | 
`public void `[`updateAllGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a2ed5c7ef47dc89d84cdf9ffdb4196010)`()` | iterates through all group references and calls updateGroupReferences for each
`public void `[`updateGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a26089d98433e280305c62f02e9014c71)`(const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & wre)` | 
`public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasInvalidGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a4faf8dce3f8189823bed6d41bb431214)`() const` | 
`public inline FILE * `[`getInFile`](#classrexgen_1_1_rexgen_parsing_driver_1a00cd4ce71c82f2546a1e4f3e0140cf5a)`() const` | 
`public inline `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`getStreamCallback`](#classrexgen_1_1_rexgen_parsing_driver_1a42ebd789a5fbf151c4342fcedc361e45)`() const` | 
`public inline void `[`handleParserError`](#classrexgen_1_1_rexgen_parsing_driver_1afefc2ac1af19e2a76a40dec36029299d)`(const char * msg) const` | 
`public inline void `[`setResult`](#classrexgen_1_1_rexgen_parsing_driver_1a01c78759e84966b9e78280df7b93869c)`(const std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` | 
`public inline std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`getResult`](#classrexgen_1_1_rexgen_parsing_driver_1ab192f11a39a4c7fe1cf61d67912e432f)`()` | 
`public std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`getStreamRegex`](#classrexgen_1_1_rexgen_parsing_driver_1ab1f3f9f4efed9c5886cb3705779f449f)`()` | this is the handling of `\0` - terminals in the regex. the first occurance of `\0` creates a [StreamRegex](#classrexgen_1_1_stream_regex) and returns it, all following occurances return a reference to the previously created [StreamRegex](#classrexgen_1_1_stream_regex). We must make this distinction, because StreamReference handles calls to next() by going to the next word, and calling next() for the whole regex would result in multiple calls to next() for each single occurance of `\0`. So, we return a [GroupReference](#classrexgen_1_1_group_reference), which does not forward the invocation of next() to the [StreamRegex](#classrexgen_1_1_stream_regex)
`private std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`result`](#classrexgen_1_1_rexgen_parsing_driver_1ab03c15d66a3f26d8aac5a35179564313) | 
`private int `[`groupId`](#classrexgen_1_1_rexgen_parsing_driver_1a65acd6a3af7e2acfd251503a86d8a1a2) | 
`private const `[`RexgenOptions`](#classrexgen_1_1_rexgen_options)` & `[`options`](#classrexgen_1_1_rexgen_parsing_driver_1acf7e6be2450fc5403f660620202d2fa3) | 
`private std::map< int, std::shared_ptr< std::set< std::shared_ptr< `[`GroupReference`](#classrexgen_1_1_group_reference)` > > > > `[`groupRefs`](#classrexgen_1_1_rexgen_parsing_driver_1a56475c89042cbd5455946c109da32255) | 
`private std::map< int, std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > `[`groups`](#classrexgen_1_1_rexgen_parsing_driver_1ac264a49c1ba5e77ca6c4fa0d8353c5dc) | 
`private std::shared_ptr< `[`StreamRegex`](#classrexgen_1_1_stream_regex)` > `[`streamRegex`](#classrexgen_1_1_rexgen_parsing_driver_1a9ba7ec9d8a09f4fdbac049d7ea41aab6) | 
`private std::shared_ptr< `[`RexgenFlexLexer`](#classrexgen_1_1_rexgen_flex_lexer)` > `[`scanner`](#classrexgen_1_1_rexgen_parsing_driver_1af1d731af44ecd6968e2f2107a4a5ee2e) | 
`private std::shared_ptr< RexgenParser > `[`parser`](#classrexgen_1_1_rexgen_parsing_driver_1ac20b8bcd610076fd01612ed8f95c7c6f) | 

### Members

#### `public  `[`RexgenParsingDriver`](#classrexgen_1_1_rexgen_parsing_driver_1af1f73446ac2b7aae7da877d1bac0ff2f)`(const `[`RexgenOptions`](#classrexgen_1_1_rexgen_options)` & __options)` 

#### `public inline int `[`nextGroupId`](#classrexgen_1_1_rexgen_parsing_driver_1aa45804ff10c026f2bfbd23ae1f01ce3f)`()` 

#### `public std::shared_ptr< `[`rexgen::Regex`](#classrexgen_1_1_regex)` > `[`parse`](#classrexgen_1_1_rexgen_parsing_driver_1a09aeb99f2d916543ca3c354805daadbe)`(const std::string & regex)` 

#### `public void `[`registerGroupReference`](#classrexgen_1_1_rexgen_parsing_driver_1ab17574ec184f293d73756b80e0b18d5a)`(std::shared_ptr< `[`GroupReference`](#classrexgen_1_1_group_reference)` > gr)` 

#### `public const std::shared_ptr< std::set< std::shared_ptr< `[`GroupReference`](#classrexgen_1_1_group_reference)` > > > & `[`getGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a90e03815b1e31440aa7e0884bd9a05c2)`(int id) const` 

#### `public void `[`registerGroup`](#classrexgen_1_1_rexgen_parsing_driver_1ad92a1e196b1abe2bb973829185803506)`(std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & re)` 

#### `public const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & `[`getGroupRegex`](#classrexgen_1_1_rexgen_parsing_driver_1ac245d64519c3f2459e35da3097d1c0e7)`(int id) const` 

#### `public const map< int, std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > & `[`getGroups`](#classrexgen_1_1_rexgen_parsing_driver_1a8faec385849c490650a444905a0e2513)`() const` 

#### `public void `[`updateAllGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a2ed5c7ef47dc89d84cdf9ffdb4196010)`()` 

iterates through all group references and calls updateGroupReferences for each

#### `public void `[`updateGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a26089d98433e280305c62f02e9014c71)`(const std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & wre)` 

#### `public `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasInvalidGroupReferences`](#classrexgen_1_1_rexgen_parsing_driver_1a4faf8dce3f8189823bed6d41bb431214)`() const` 

#### `public inline FILE * `[`getInFile`](#classrexgen_1_1_rexgen_parsing_driver_1a00cd4ce71c82f2546a1e4f3e0140cf5a)`() const` 

#### `public inline `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`getStreamCallback`](#classrexgen_1_1_rexgen_parsing_driver_1a42ebd789a5fbf151c4342fcedc361e45)`() const` 

#### `public inline void `[`handleParserError`](#classrexgen_1_1_rexgen_parsing_driver_1afefc2ac1af19e2a76a40dec36029299d)`(const char * msg) const` 

#### `public inline void `[`setResult`](#classrexgen_1_1_rexgen_parsing_driver_1a01c78759e84966b9e78280df7b93869c)`(const std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & regex)` 

#### `public inline std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`getResult`](#classrexgen_1_1_rexgen_parsing_driver_1ab192f11a39a4c7fe1cf61d67912e432f)`()` 

#### `public std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`getStreamRegex`](#classrexgen_1_1_rexgen_parsing_driver_1ab1f3f9f4efed9c5886cb3705779f449f)`()` 

this is the handling of `\0` - terminals in the regex. the first occurance of `\0` creates a [StreamRegex](#classrexgen_1_1_stream_regex) and returns it, all following occurances return a reference to the previously created [StreamRegex](#classrexgen_1_1_stream_regex). We must make this distinction, because StreamReference handles calls to next() by going to the next word, and calling next() for the whole regex would result in multiple calls to next() for each single occurance of `\0`. So, we return a [GroupReference](#classrexgen_1_1_group_reference), which does not forward the invocation of next() to the [StreamRegex](#classrexgen_1_1_stream_regex)

#### `private std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > `[`result`](#classrexgen_1_1_rexgen_parsing_driver_1ab03c15d66a3f26d8aac5a35179564313) 

#### `private int `[`groupId`](#classrexgen_1_1_rexgen_parsing_driver_1a65acd6a3af7e2acfd251503a86d8a1a2) 

#### `private const `[`RexgenOptions`](#classrexgen_1_1_rexgen_options)` & `[`options`](#classrexgen_1_1_rexgen_parsing_driver_1acf7e6be2450fc5403f660620202d2fa3) 

#### `private std::map< int, std::shared_ptr< std::set< std::shared_ptr< `[`GroupReference`](#classrexgen_1_1_group_reference)` > > > > `[`groupRefs`](#classrexgen_1_1_rexgen_parsing_driver_1a56475c89042cbd5455946c109da32255) 

#### `private std::map< int, std::weak_ptr< `[`Regex`](#classrexgen_1_1_regex)` > > `[`groups`](#classrexgen_1_1_rexgen_parsing_driver_1ac264a49c1ba5e77ca6c4fa0d8353c5dc) 

#### `private std::shared_ptr< `[`StreamRegex`](#classrexgen_1_1_stream_regex)` > `[`streamRegex`](#classrexgen_1_1_rexgen_parsing_driver_1a9ba7ec9d8a09f4fdbac049d7ea41aab6) 

#### `private std::shared_ptr< `[`RexgenFlexLexer`](#classrexgen_1_1_rexgen_flex_lexer)` > `[`scanner`](#classrexgen_1_1_rexgen_parsing_driver_1af1d731af44ecd6968e2f2107a4a5ee2e) 

#### `private std::shared_ptr< RexgenParser > `[`parser`](#classrexgen_1_1_rexgen_parsing_driver_1ac20b8bcd610076fd01612ed8f95c7c6f) 

## class `rexgen::StreamRegex` 

```
class rexgen::StreamRegex
  : public rexgen::Regex
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_stream_regex_1a8775c73955a20e0b07a479bae9056785)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` | 
`public  explicit `[`StreamRegex`](#classrexgen_1_1_stream_regex_1a1ad536c4cd09594d56f1206afd587644)`(`[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` cb)` | 
`public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_stream_regex_1ae8a641628e3876d49df5903fa3705ff7)`() const` | 
`public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`usesCallback`](#classrexgen_1_1_stream_regex_1ace6da3e326b6025a0328add693692b91)`() const` | 
`private `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`callback`](#classrexgen_1_1_stream_regex_1ad2269ee67ad44e3c2f8d9e74586dfafd) | 

### Members

#### `public virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_stream_regex_1a8775c73955a20e0b07a479bae9056785)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` & state) const` 

#### `public  explicit `[`StreamRegex`](#classrexgen_1_1_stream_regex_1a1ad536c4cd09594d56f1206afd587644)`(`[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` cb)` 

#### `public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_stream_regex_1ae8a641628e3876d49df5903fa3705ff7)`() const` 

#### `public inline virtual `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`usesCallback`](#classrexgen_1_1_stream_regex_1ace6da3e326b6025a0328add693692b91)`() const` 

#### `private `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`callback`](#classrexgen_1_1_stream_regex_1ad2269ee67ad44e3c2f8d9e74586dfafd) 

## class `rexgen::StreamRegexIterator` 

```
class rexgen::StreamRegexIterator
  : public Iterator
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator_1ab1d706a473498a77bafac86e75dc54bf)`(`[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` cb)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_stream_regex_iterator_1a31d4076269f1a7ece91dfbf4889cc40f)`()` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`forceNext`](#classrexgen_1_1_stream_regex_iterator_1ac84185d9685d89ed3bfa914f76a8d1cc)`()` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_stream_regex_iterator_1aa9ff05fe9d8234df4a891469495be216)`() const` | 
`public inline void `[`value`](#classrexgen_1_1_stream_regex_iterator_1a83e2398e9032e9c7844159cb4cf721fd)`(SimpleString * dst) const` | 
`public inline void `[`updateReferences`](#classrexgen_1_1_stream_regex_iterator_1a69b572e778517979f74658049a21e242)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline void `[`updateAttributes`](#classrexgen_1_1_stream_regex_iterator_1adf0af7e80139f941194162fa75958549)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`isSingleton`](#classrexgen_1_1_stream_regex_iterator_1a47ffc252988b9d0ed5578f5aeda70c3d)`() const` | 
`public std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_stream_regex_iterator_1a249bafc4cbf51c2ef71e1d082d904ac5)`() const` | 
`public void `[`setCurrentState`](#classrexgen_1_1_stream_regex_iterator_1aa2b5ec3b92ff3554769cc417a4bf3df1)`(const std::shared_ptr< SerializableState > & state)` | 
`private `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`callback`](#classrexgen_1_1_stream_regex_iterator_1a58c7992ae0138c87833c1cbd9fe5a8d4) | 
`private `[`byte_t`](#defs_8h_1af0f045fc129737ba472182df02d418db)` `[`buffer`](#classrexgen_1_1_stream_regex_iterator_1adbcb3b0b89a57f22d758e6ce9db52da8) | 
`private size_t `[`length`](#classrexgen_1_1_stream_regex_iterator_1abc3583081c0297e5810fb6f49770b9f4) | 
`private `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`__hasNext`](#classrexgen_1_1_stream_regex_iterator_1adfc97bb6fbe75db5e9cc9b32f3fa7a82) | 
`private void `[`readNextWord`](#classrexgen_1_1_stream_regex_iterator_1a69a3c1293314e911ce42409bea4366d0)`()` | 

### Members

#### `public inline  `[`StreamRegexIterator`](#classrexgen_1_1_stream_regex_iterator_1ab1d706a473498a77bafac86e75dc54bf)`(`[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` cb)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_stream_regex_iterator_1a31d4076269f1a7ece91dfbf4889cc40f)`()` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`forceNext`](#classrexgen_1_1_stream_regex_iterator_1ac84185d9685d89ed3bfa914f76a8d1cc)`()` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_stream_regex_iterator_1aa9ff05fe9d8234df4a891469495be216)`() const` 

#### `public inline void `[`value`](#classrexgen_1_1_stream_regex_iterator_1a83e2398e9032e9c7844159cb4cf721fd)`(SimpleString * dst) const` 

#### `public inline void `[`updateReferences`](#classrexgen_1_1_stream_regex_iterator_1a69b572e778517979f74658049a21e242)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline void `[`updateAttributes`](#classrexgen_1_1_stream_regex_iterator_1adf0af7e80139f941194162fa75958549)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`isSingleton`](#classrexgen_1_1_stream_regex_iterator_1a47ffc252988b9d0ed5578f5aeda70c3d)`() const` 

#### `public std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_stream_regex_iterator_1a249bafc4cbf51c2ef71e1d082d904ac5)`() const` 

#### `public void `[`setCurrentState`](#classrexgen_1_1_stream_regex_iterator_1aa2b5ec3b92ff3554769cc417a4bf3df1)`(const std::shared_ptr< SerializableState > & state)` 

#### `private `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`callback`](#classrexgen_1_1_stream_regex_iterator_1a58c7992ae0138c87833c1cbd9fe5a8d4) 

#### `private `[`byte_t`](#defs_8h_1af0f045fc129737ba472182df02d418db)` `[`buffer`](#classrexgen_1_1_stream_regex_iterator_1adbcb3b0b89a57f22d758e6ce9db52da8) 

#### `private size_t `[`length`](#classrexgen_1_1_stream_regex_iterator_1abc3583081c0297e5810fb6f49770b9f4) 

#### `private `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`__hasNext`](#classrexgen_1_1_stream_regex_iterator_1adfc97bb6fbe75db5e9cc9b32f3fa7a82) 

#### `private void `[`readNextWord`](#classrexgen_1_1_stream_regex_iterator_1a69a3c1293314e911ce42409bea4366d0)`()` 

## class `rexgen::TerminalRegex` 

```
class rexgen::TerminalRegex
  : public rexgen::Regex
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`TerminalRegex`](#classrexgen_1_1_terminal_regex_1a2034fea2c0eb6e660dcf015fb8cdbbf4)`(wchar_t ch)` | 
`public void `[`prepend`](#classrexgen_1_1_terminal_regex_1aa6c2b7f80ac10111373fd329ba74ab16)`(const std::shared_ptr< `[`TerminalRegex`](#classrexgen_1_1_terminal_regex)` > & tre)` | 
`public inline const `[`char_type`](#unicode_8h_1a1795bbf724aa995adcfd886242d42be3)` * `[`getValue`](#classrexgen_1_1_terminal_regex_1a759dec4e3b57573f82e21d3ee8c21d49)`() const` | 
`public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_terminal_regex_1a70b4643d361531385d1b5fb9f381a1d4)`() const` | 
`public inline virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_terminal_regex_1a8730f68305799638e8f6cfc7f6fe02a7)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &) const` | 
`private std::vector< wchar_t > `[`value`](#classrexgen_1_1_terminal_regex_1abfd47df99e4079c379ed09cb12557c16) | 

### Members

#### `public inline  explicit `[`TerminalRegex`](#classrexgen_1_1_terminal_regex_1a2034fea2c0eb6e660dcf015fb8cdbbf4)`(wchar_t ch)` 

#### `public void `[`prepend`](#classrexgen_1_1_terminal_regex_1aa6c2b7f80ac10111373fd329ba74ab16)`(const std::shared_ptr< `[`TerminalRegex`](#classrexgen_1_1_terminal_regex)` > & tre)` 

#### `public inline const `[`char_type`](#unicode_8h_1a1795bbf724aa995adcfd886242d42be3)` * `[`getValue`](#classrexgen_1_1_terminal_regex_1a759dec4e3b57573f82e21d3ee8c21d49)`() const` 

#### `public inline virtual `[`RegexType`](#namespacerexgen_1a6879451674c9a37eb56e3a1526f19f56)` `[`getRegexType`](#classrexgen_1_1_terminal_regex_1a70b4643d361531385d1b5fb9f381a1d4)`() const` 

#### `public inline virtual std::unique_ptr< Iterator > `[`singleIterator`](#classrexgen_1_1_terminal_regex_1a8730f68305799638e8f6cfc7f6fe02a7)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &) const` 

#### `private std::vector< wchar_t > `[`value`](#classrexgen_1_1_terminal_regex_1abfd47df99e4079c379ed09cb12557c16) 

## class `rexgen::TerminalRegexIterator` 

```
class rexgen::TerminalRegexIterator
  : public Iterator
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  `[`TerminalRegexIterator`](#classrexgen_1_1_terminal_regex_iterator_1a9704867a69cd34702fec715c1abcd6d5)`(const wchar_t * _terminal,size_t elements)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_terminal_regex_iterator_1a4cd4c5726d62031ce7934b105cd882b0)`()` | 
`public inline void `[`value`](#classrexgen_1_1_terminal_regex_iterator_1ac9288ed335edb524a460f4f3ccbc42bf)`(SimpleString * dst) const` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_terminal_regex_iterator_1a5e0a76b33048b00c73b8f32c55559853)`() const` | 
`public inline void `[`updateReferences`](#classrexgen_1_1_terminal_regex_iterator_1a8cd82f85fd420379aad6ec17d9ea7e9c)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline void `[`updateAttributes`](#classrexgen_1_1_terminal_regex_iterator_1af24e124f4ea77f59e7cc7af5f8aa51e7)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`private SimpleString `[`terminal`](#classrexgen_1_1_terminal_regex_iterator_1a5c23895f1f6161a315a5c9d33758c6e4) | 

### Members

#### `public inline  `[`TerminalRegexIterator`](#classrexgen_1_1_terminal_regex_iterator_1a9704867a69cd34702fec715c1abcd6d5)`(const wchar_t * _terminal,size_t elements)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_terminal_regex_iterator_1a4cd4c5726d62031ce7934b105cd882b0)`()` 

#### `public inline void `[`value`](#classrexgen_1_1_terminal_regex_iterator_1ac9288ed335edb524a460f4f3ccbc42bf)`(SimpleString * dst) const` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`hasNext`](#classrexgen_1_1_terminal_regex_iterator_1a5e0a76b33048b00c73b8f32c55559853)`() const` 

#### `public inline void `[`updateReferences`](#classrexgen_1_1_terminal_regex_iterator_1a8cd82f85fd420379aad6ec17d9ea7e9c)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline void `[`updateAttributes`](#classrexgen_1_1_terminal_regex_iterator_1af24e124f4ea77f59e7cc7af5f8aa51e7)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `private SimpleString `[`terminal`](#classrexgen_1_1_terminal_regex_iterator_1a5c23895f1f6161a315a5c9d33758c6e4) 

## class `rexgen::TopIterator` 

```
class rexgen::TopIterator
  : public Iterator
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`TopIterator`](#classrexgen_1_1_top_iterator_1a7d03a410aca435f58712da95e147e6f8)`(std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & re)` | 
`public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_top_iterator_1adc2e372c7d4bcb12dd59d59abb574e6d)`()` | 
`public inline void `[`value`](#classrexgen_1_1_top_iterator_1a67a454823d6fb2ae1d295deadec73e06)`(SimpleString * dst) const` | 
`public inline void `[`updateReferences`](#classrexgen_1_1_top_iterator_1afe394d7a792e741d25e71f07984ab013)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline void `[`updateAttributes`](#classrexgen_1_1_top_iterator_1a0a826701e9792e30c26821d7a573b636)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` | 
`public inline std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_top_iterator_1a17db910589cb2287d4a1100a25fc7989)`() const` | 
`public inline void `[`setCurrentState`](#classrexgen_1_1_top_iterator_1a99548f48c77ed9754cc4ec96852872a4)`(const std::shared_ptr< SerializableState > & s)` | 
`private std::shared_ptr< Iterator > `[`child`](#classrexgen_1_1_top_iterator_1ae0a02b5fb9eeca42673ef03b60a46de9) | 
`private `[`IteratorState`](#classrexgen_1_1_iterator_state)` `[`state`](#classrexgen_1_1_top_iterator_1a95b206dc0d60a3a80a863dda0aaad571) | 
`private `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`needWord`](#classrexgen_1_1_top_iterator_1a30f87bf61f6278216f2b025211db0e47) | 
`private inline void `[`updateReferences`](#classrexgen_1_1_top_iterator_1ad7a5a816642bf6d1877ac9b98c22df9b)`()` | 
`private inline void `[`updateAttributes`](#classrexgen_1_1_top_iterator_1a42475faf8f8155f9ae16a3bf1bfae436)`()` | 

### Members

#### `public inline  explicit `[`TopIterator`](#classrexgen_1_1_top_iterator_1a7d03a410aca435f58712da95e147e6f8)`(std::shared_ptr< `[`Regex`](#classrexgen_1_1_regex)` > & re)` 

#### `public inline `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`next`](#classrexgen_1_1_top_iterator_1adc2e372c7d4bcb12dd59d59abb574e6d)`()` 

#### `public inline void `[`value`](#classrexgen_1_1_top_iterator_1a67a454823d6fb2ae1d295deadec73e06)`(SimpleString * dst) const` 

#### `public inline void `[`updateReferences`](#classrexgen_1_1_top_iterator_1afe394d7a792e741d25e71f07984ab013)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline void `[`updateAttributes`](#classrexgen_1_1_top_iterator_1a0a826701e9792e30c26821d7a573b636)`(`[`IteratorState`](#classrexgen_1_1_iterator_state)` &)` 

#### `public inline std::shared_ptr< SerializableState > `[`getCurrentState`](#classrexgen_1_1_top_iterator_1a17db910589cb2287d4a1100a25fc7989)`() const` 

#### `public inline void `[`setCurrentState`](#classrexgen_1_1_top_iterator_1a99548f48c77ed9754cc4ec96852872a4)`(const std::shared_ptr< SerializableState > & s)` 

#### `private std::shared_ptr< Iterator > `[`child`](#classrexgen_1_1_top_iterator_1ae0a02b5fb9eeca42673ef03b60a46de9) 

#### `private `[`IteratorState`](#classrexgen_1_1_iterator_state)` `[`state`](#classrexgen_1_1_top_iterator_1a95b206dc0d60a3a80a863dda0aaad571) 

#### `private `[`bool`](#rexgen_8c_1a1062901a7428fdd9c7f180f5e01ea056)` `[`needWord`](#classrexgen_1_1_top_iterator_1a30f87bf61f6278216f2b025211db0e47) 

#### `private inline void `[`updateReferences`](#classrexgen_1_1_top_iterator_1ad7a5a816642bf6d1877ac9b98c22df9b)`()` 

#### `private inline void `[`updateAttributes`](#classrexgen_1_1_top_iterator_1a42475faf8f8155f9ae16a3bf1bfae436)`()` 

## struct `rexgen::t_group_options` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public int `[`handle_case`](#structrexgen_1_1t__group__options_1aee4b97d9c9d16215a4eae29bbd915621) | 
`public int `[`group_id`](#structrexgen_1_1t__group__options_1ae75ec2d160f5479b1bd4b48496862525) | 
`public inline  `[`t_group_options`](#structrexgen_1_1t__group__options_1aedab8a73af2083c48b91b37a52026493)`(int gid)` | 
`public inline  `[`t_group_options`](#structrexgen_1_1t__group__options_1a70944c307bd72cf3b306c45fd5258124)`(int hc,int gid)` | 

### Members

#### `public int `[`handle_case`](#structrexgen_1_1t__group__options_1aee4b97d9c9d16215a4eae29bbd915621) 

#### `public int `[`group_id`](#structrexgen_1_1t__group__options_1ae75ec2d160f5479b1bd4b48496862525) 

#### `public inline  `[`t_group_options`](#structrexgen_1_1t__group__options_1aedab8a73af2083c48b91b37a52026493)`(int gid)` 

#### `public inline  `[`t_group_options`](#structrexgen_1_1t__group__options_1a70944c307bd72cf3b306c45fd5258124)`(int hc,int gid)` 

## class `GenericError` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`GenericError`](#class_generic_error_1ae4e764e60ce9bfd04e66cf39e05ef25b)`(const char * msg)` | 
`public inline  explicit `[`GenericError`](#class_generic_error_1aab2c99a2e74260ec350bf5b1dcf712a5)`(const std::string & msg)` | 
`public inline const char * `[`getMessage`](#class_generic_error_1af854f7e655966246710c49e425e03ce6)`()` | 
`private const std::string `[`message`](#class_generic_error_1af4196cf6da0d8db9d828594c08d2cd2d) | 

### Members

#### `public inline  explicit `[`GenericError`](#class_generic_error_1ae4e764e60ce9bfd04e66cf39e05ef25b)`(const char * msg)` 

#### `public inline  explicit `[`GenericError`](#class_generic_error_1aab2c99a2e74260ec350bf5b1dcf712a5)`(const std::string & msg)` 

#### `public inline const char * `[`getMessage`](#class_generic_error_1af854f7e655966246710c49e425e03ce6)`()` 

#### `private const std::string `[`message`](#class_generic_error_1af4196cf6da0d8db9d828594c08d2cd2d) 

## class `SyntaxError` 

```
class SyntaxError
  : public GenericError
```

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public inline  explicit `[`SyntaxError`](#class_syntax_error_1ab3878309034fbf0906f18d7dbd8958cc)`(const char * msg)` | 
`public inline  explicit `[`SyntaxError`](#class_syntax_error_1a95a39044feb3a788f3960f3c05ecdde4)`(const std::string & msg)` | 

### Members

#### `public inline  explicit `[`SyntaxError`](#class_syntax_error_1ab3878309034fbf0906f18d7dbd8958cc)`(const char * msg)` 

#### `public inline  explicit `[`SyntaxError`](#class_syntax_error_1a95a39044feb3a788f3960f3c05ecdde4)`(const std::string & msg)` 

## struct `_RexgenOptions` 

### Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`stream_callback`](#struct___rexgen_options_1a9c888dadc64ee7be76091cbb442ad64c) | 
`public const char * `[`regex_ctype`](#struct___rexgen_options_1a6d58d77e8e23ac89e19b68839d215f2e) | 
`public const char * `[`callback_ctype`](#struct___rexgen_options_1adb9224a00b13c8685d10ab894dc83dd6) | 

### Members

#### `public `[`callback_fp_mb`](#types_8h_1abf0394cb4342978d6ae0ad8d50a5628f)` `[`stream_callback`](#struct___rexgen_options_1a9c888dadc64ee7be76091cbb442ad64c) 

#### `public const char * `[`regex_ctype`](#struct___rexgen_options_1a6d58d77e8e23ac89e19b68839d215f2e) 

#### `public const char * `[`callback_ctype`](#struct___rexgen_options_1adb9224a00b13c8685d10ab894dc83dd6) 

Generated by [Moxygen](https://sourcey.com/moxygen)