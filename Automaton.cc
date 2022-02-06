#include "Automaton.h"

namespace fa {
  /**
   * @brief Private recursive function that runs throught the automaton trying to find a final state, begining by the initials states
   * (Used in isLanguageEmpty())
   * @param state the current state
   * @param visited the set of states already visited
   * @return true if a final state is find
   * @return false if a final state hasn't be found
   */
  bool Automaton::depthFirstSearch(int state, std::set<int> &visited) const{
    if(isStateFinal(state)){
      return true;
    }
    visited.insert(state);
    for(auto const adjacent_state : map_arcs){
      if(adjacent_state.first == state){
        if(visited.find(adjacent_state.second.to) == visited.end()){
          if(depthFirstSearch(adjacent_state.second.to, visited)){
            return true;
          }
        }
      }
    }
    return false;
  }

  /**
   * @brief Private recursive function that runs throught the automaton trying to find all states, begining by the initials states
   * (Used for RemoveNonAssessible())
   * @param state the current state
   * @param visited the set of states already visited
   */
  void Automaton::depthFirstSearch_NonAccessible(int state, std::set<int> &visited) const{
    visited.insert(state);
    for(auto const adjacent_state : map_arcs){
      if(adjacent_state.first == state){
        if(visited.find(adjacent_state.second.to) == visited.end()){
          depthFirstSearch_NonAccessible(adjacent_state.second.to, visited);
        }
      }
    }
  }

  /**
   * @brief Private recursive function that runs throught the automaton trying to find all states, begining by the finals states
   * (Used for RemoveNonCoAssessible())
   * @param state the current state
   * @param visited the set of states already visited
   */
  void Automaton::depthFirstSearch_NonCoAccessible(int state, std::set<int> &visited) const{
    visited.insert(state);
    for(auto const adjacent_state : map_arcs){
      if(adjacent_state.second.to == state){
        if(visited.find(adjacent_state.first) == visited.end()){
          depthFirstSearch_NonCoAccessible(adjacent_state.first, visited);
        }
      }
    }
  }

  /**
   * @brief Private recursive function that try to find the state(s) where the word end, begining by the initials states
   * (Used for ReadString())
   * @param state the current state
   * @param word the word that we try to find where it will end
   * @return std::set<int> the state(s) where the word can end 
   */
  std::set<int> Automaton::endStateOfWord(int state, const std::string& word) const{
    std::set<int> rtn_set;

    if(word.size() == 0){
      rtn_set.insert(state);
    }else{
      for(auto const adjacent_state : map_arcs){
        if(adjacent_state.first == state){
          if(adjacent_state.second.alpha == *word.begin()){
            std::set<int> recursiv_set = endStateOfWord(adjacent_state.second.to, word.substr(1));
            std::set<int> merged_set;
            std::merge(rtn_set.begin(), rtn_set.end(), recursiv_set.begin(), recursiv_set.end(), std::inserter(merged_set, merged_set.end()));
            rtn_set = merged_set;
          }
        }
      }
    }

    return rtn_set;
  }

  /**
   * @brief Private function that unset a state final > the state become a non final state
   * 
   * @param state the number of the state we want to remove the property
   */
  void Automaton::unsetStateFinal(int state){
    if(hasState(state)){
      auto search = map_states.find(state);
      if(search != map_states.end()){
        search->second.isFinal = false;
      }
    }
  }


  Automaton::Automaton() {
  }

  // ------------------- 2.1

  /**
   * @brief Tell if the current automaton is valid
   * 
   * @return true if it has atleast one letter in the alphabet and atleast one state
   * @return false 
   */
  bool Automaton::isValid() const {
    return (countSymbols() != 0 && countStates() != 0);
  }

  // ------------------- 2.2

  /**
   * @brief Add the letter if the current automaton's alphabet hasn't it, and return true if it's success
   * 
   * @param symbol the letter that the function will want to add
   * @return true if the add succeed
   * @return false if the add failed
   */
  bool Automaton::addSymbol(char symbol) {
    if(symbol == Epsilon || !isgraph(symbol)){
      return false;
    }
    std::pair<std::set<char>::iterator,bool> ret = alphabet.insert(symbol);
    return ret.second;
  }

  /**
   * @brief Remove the letter if the current automaton's alphabet has it, and return true if it's success
   * 
   * @param symbol the letter that the function will want to remove
   * @return true if the add succeed
   * @return false if the add failed
   */
  bool Automaton::removeSymbol(char symbol) {
    if(hasSymbol(symbol)){
      for(auto arc = map_arcs.begin(); arc != map_arcs.end(); ){
        if(arc->second.alpha == symbol){
         arc = map_arcs.erase(arc);
        }else{
          ++arc;
        }
      }
      alphabet.erase(symbol);
      return true;
    }
    return false;
  }

  /**
   * @brief Tell if the current automaton's alphabet has the letter
   * 
   * @param symbol the letter that the function will search
   * @return true if the current automaton's alphabet has this letter
   * @return false if the current automaton's alphabet hasn't this letter
   */
  bool Automaton::hasSymbol(char symbol) const {
    if(symbol == Epsilon || !isgraph(symbol)){
      return false;
    }
    for(char chr : alphabet){
      if(chr == symbol){
        return true;
      }
    }
    return false;
  }
  /**
   * @brief count the number of letter the current automaton's alphabet
   * 
   * @return std::size_t the number of letter the automaton's alphabet has
   */
  std::size_t Automaton::countSymbols () const{
    return (size_t) alphabet.size();
  }

   // ------------------- 2.3
  /**
   * @brief Add the state if the current automaton hasn't it, and return true if it's success
   * 
   * @param state the number of the state that the function will give 
   * @return true if the add succeed
   * @return false if the add failed
   */
  bool Automaton::addState(int state) {
    if(state < 0){
      return false;
    }
    State state1{state, false, false};
    std::pair<std::map<int, State>::iterator, bool> ret = map_states.insert({state, state1});
    return ret.second;
  }

  /**
   * @brief Remove the state if the current automaton has it, and return true if it's success
   * 
   * @param state the number of the state that the function will want to remove
   * @return true if the add succeed
   * @return false if the add failed
   */
  bool Automaton::removeState(int state) {
    if(hasState(state)){
      for(auto arc = map_arcs.begin(); arc != map_arcs.end(); ){
        if(arc->first == state || arc->second.to == state){
          arc = map_arcs.erase(arc);
        }else{
          ++arc;
        }
      }
      map_states.erase(state);
      return true;
    }
    return false;
  }

  /**
   * @brief Tell if the current automaton has the state
   * 
   * @param from the number of the state the function will search
   * @return true if the current automaton has this state
   * @return false if the current automaton hasn't this state
   */
  bool Automaton::hasState(int state) const {
    if(state < 0){
      return false;
    }
    auto search = map_states.find(state);
    if(search != map_states.end()){
      return true;
    }
    return false;
  }

  /**
   * @brief count the number of state the current automaton has
   * 
   * @return std::size_t the number of state the automaton has
   */
  std::size_t Automaton::countStates () const{
    return (size_t) map_states.size();
  }


  // ------------------- 2.4
  /**
   * @brief make the state initial
   * 
   * @param state the state that we want to be initial
   */
  void Automaton::setStateInitial(int state){
    if(hasState(state)){
      auto search = map_states.find(state);
      if(search != map_states.end()){
        search->second.isInitial = true;
      }
    }
  }

  /**
   * @brief Tell if the state in parameter is initial
   * 
   * @param state The state that we will check
   * @return true if the state is initial
   * @return false if the state is initial
   */
  bool Automaton::isStateInitial(int state) const{
    if(hasState(state)){
      auto search = map_states.find(state);
        if(search != map_states.end()){
          return search->second.isInitial == true;
        }
    }
    return false;
  }
  
  /**
   * @brief make the state final
   * 
   * @param state the state that we want to be final
   */
  void Automaton::setStateFinal(int state){
    if(hasState(state)){
      auto search = map_states.find(state);
      if(search != map_states.end()){
        search->second.isFinal = true;
      }
    }
  }

  /**
   * @brief Tell if the state in parameter is final
   * 
   * @param state The state that we will check
   * @return true if the state is final
   * @return false if the state is final
   */
  bool Automaton::isStateFinal(int state) const{
    if(hasState(state)){
      auto search = map_states.find(state);
        if(search != map_states.end()){
          return search->second.isFinal == true;
        }
    }
    return false;
  }

   // ------------------- 2.5
  /**
   * @brief Add the transition if the current automaton hasn't it, and return true if it's success
   * 
   * @param from where the transition come from
   * @param alpha by what letter the transition will go
   * @param to where the transition is aiming
   * @return true if the add succeed
   * @return false if the add failed
   */
  bool Automaton::addTransition(int from, char alpha, int to) {
    if(from < 0 || to < 0 ){
      return false;
    }
    if(!isgraph(alpha) && alpha != fa::Epsilon){
      return false;
    }
    if(!hasSymbol(alpha) && alpha != fa::Epsilon){
      return false;
    }
    if(!hasState(from) || !hasState(to)){
      return false;
    }
    if(hasTransition(from, alpha, to)){
      return false;
    }
    Arc arc1{from, alpha, to};
    map_arcs.insert({from, arc1});
    return true;
  }

  /**
   * @brief Remove the transition if the current automaton has it, and return true if it's success
   * 
   * @param from where the transition come from
   * @param alpha by what letter the transition will go
   * @param to where the transition is aiming
   * @return true if the remove succeed
   * @return false if the remove failed
   */
  bool Automaton::removeTransition(int from, char alpha, int to) {
    auto search = map_arcs.find(from);
    for (auto i = search; i != map_arcs.end(); i++){
      if(i -> second.alpha == alpha && i -> second.to == to){
        map_arcs.erase(i);
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Tell if the current automaton has the transition
   * 
   * @param from where the transition come from
   * @param alpha by what letter the transition will go
   * @param to where the transition is aiming
   * @return true if the current automaton has this transition
   * @return false if the current automaton hasn't this transition
   */
  bool Automaton::hasTransition(int from, char alpha, int to) const {
    if(from < 0 || to < 0){
      return false;
    }
    if(!isgraph(alpha) && alpha != fa::Epsilon){
      return false;
    }
    if(!hasSymbol(alpha) && alpha != fa::Epsilon){
      return false;
    }
    if(!hasState(from) || !hasState(to)){
      return false;
    }
    auto search = map_arcs.find(from);
    for (auto i = search; i != map_arcs.end(); i++){
      if(i -> second.from == from && i -> second.alpha == alpha && i -> second.to == to){
        return true;
      }
    }
    return false;
  }

  /**
   * @brief Function that draws the current automaton on the stream in parameter
   * 
   * @param os where the function should draw the automaton
   */
  void Automaton::prettyPrint(std::ostream& os) const{
    os << "Initial states :" << std::endl;
    for(auto const state : map_states){
      if(state.second.isInitial){
        os << "\t " << state.first << std::endl;
      }
    }
    os << "Final states :" << std::endl;
    for(auto const state : map_states){
      if(state.second.isFinal){
        os << "\t " << state.first << std::endl;
      }
    }
    os << "Transitions :" << std::endl;
    for(auto const state : map_states){
      os << "\t For state " << state.first << " : " << std::endl;
      for(auto const letter : alphabet){
        os << "\t\t For letter " << letter << " : ";
        for(auto const arc : map_arcs){
          if(arc.first == state.first && arc.second.alpha == letter){
            os << arc.second.to << " ";
          }
        }
        os << "\n" << std::endl;
      }
    }
  }

  /**
   * @brief count the number of transitions that the current automaton has
   * 
   * @return std::size_t the number of transitions the automaton has
   */
  std::size_t Automaton::countTransitions () const{
    return map_arcs.size();
  }

   // ------------------- 3 Propriété d'un automate
  /**
   * @brief tell if the current automaton has epsilon transtions 
   * 
   * @return true if the current automaton has epsilon transitions
   * @return false if the current automaton has epsilon transitions
   */
  bool Automaton::hasEpsilonTransition () const{
    assert(isValid());
    for(auto const arc : map_arcs){
      if(arc.second.alpha == Epsilon){
        return true;
      }
    }
    return false;
  }

  /**
   * @brief tell if the current automaton is deterministic
   * 
   * @return true if the current automaton is deterministic
   * @return false if the current automaton is deterministic
   */
  bool Automaton::isDeterministic () const{
    assert(isValid());
    size_t initiaux = 0;
    for(auto const initial : map_states){
      if(isStateInitial(initial.first)){
        initiaux++;
      }
    }
    if(initiaux != 1){
      return false;
    }
    for(auto const state1 : map_states){
      for(auto const letter : alphabet){
        int count = 0;
        for(auto const arc : map_arcs){
          if(arc.first == state1.first && arc.second.alpha == letter){
            count++;
          }
        }
        if(count > 1){
          return false;
        }
      }
    }
    return true;
  }

  /**
   * @brief tell if the current automaton is complete
   * 
   * @return true if the current automaton is complete
   * @return false if the current automaton isn't complete
   */
  bool Automaton::isComplete () const{
    assert(isValid());
    for(auto const state1 : map_states){
      for(auto const letter : alphabet){
        int count = 0;
        for(auto const arc : map_arcs){
          if(arc.first == state1.first && arc.second.alpha == letter){
            count++;
          }
        }
        if(count < 1){
          return false;
        }
      }
    }
    return true;
  }

   // ------------------- 4 Transformation simple d'un automate
  /**
   * @brief Create a complete Automaton if it is not already
   * 
   * @param other the Automaton that we will use to create his complete version
   * @return a complete Automaton
   */
  Automaton Automaton::createComplete(const Automaton& automaton){
    assert(automaton.isValid());
    if(automaton.isComplete()){
      return automaton;
    }

    Automaton automate = automaton;
    int etat_puit = 0;
    bool isUsed = false;
    for(std::size_t etat_puit_it = 0; etat_puit_it <= automaton.countStates(); etat_puit_it++){
      etat_puit = (int)etat_puit_it;
      if(automate.addState(etat_puit)){
        break;
      }
    }

    for(auto const state1 : automate.map_states){
      for(auto const letter : automate.alphabet){
        int count = 0;
        for(auto const arc : automate.map_arcs){
          if(arc.first == state1.first && arc.second.alpha == letter){
            count++;
          }
        }
        std::set<int> visited;
        if(count < 1){
          if(automate.depthFirstSearch(state1.first,visited)){
            automate.addTransition(state1.first, letter, etat_puit);
            isUsed = true;
          }else{
            automate.addTransition(state1.first, letter, state1.first);
          }
        }
      }
    }

    if(!isUsed){
      automate.removeState(etat_puit);
    }

    return automate;
  }

  /**
   * @brief Create the complement Automaton of the automaton in parameter
   * 
   * @param other the Automaton that we will use to create his complement
   * @return the complement Automaton
   */
  Automaton Automaton::createComplement(const Automaton& automaton){
    assert(automaton.isValid());

    Automaton complement = automaton;

    complement = automaton.createDeterministic(automaton);
    complement = complement.createComplete(complement);

    for(auto state : complement.map_states){
      if(!complement.isStateFinal(state.first)){
        complement.setStateFinal(state.first);
      }else{
        complement.unsetStateFinal(state.first);
      }
    }

    return complement;
  }

  /**
   * @brief Create a mirror Automaton of the automaton in parameter
   * 
   * @param other the Automaton that we will use to create his mirror version
   * @return the mirror Automaton
   */
  Automaton Automaton::createMirror(const Automaton& automaton){
    // Les initiaux deviennent finaux 
    // Les finaux deviennent initiaux
    // Inversé le sens des flèches
    assert(automaton.isValid());

    Automaton automate;
    automate.alphabet = automaton.alphabet;

    for(auto const state : automaton.map_states){
      automate.addState(state.first);
      if(automaton.isStateInitial(state.first)){
        automate.setStateFinal(state.first);
      }if(automaton.isStateFinal(state.first)){
        automate.setStateInitial(state.first);
      }
    }
    for(auto const arc : automaton.map_arcs){
      automate.addTransition(arc.second.to, arc.second.alpha, arc.first);
    }
    return automate;
  }

  // ------------------- 5 Test du vide
  /**
   * @brief Tell if the language of the current automaton is empty or not
   * 
   * @return true if the language is empty
   * @return false if the language isn't empty
   */
  bool Automaton::isLanguageEmpty() const{
    assert(isValid());
    std::set <int> set_initial_state;
    bool has_final_state = false;
    for(auto const state : map_states){
      if(isStateInitial(state.first)){
        set_initial_state.insert(state.first);
      }
      if(isStateFinal(state.first)){
        has_final_state = true;
      }
    }
    if(set_initial_state.empty() || !has_final_state){
      return true;
    }

    std::set<int> visited;
    for(auto const inital_state : set_initial_state){
      if(depthFirstSearch(inital_state, visited)){
        return false;
      }
    }
    return true;
  }

  // ------------------- 6 Suppression des états inutiles
  /**
   * @brief remove the non-accessibles states of the current automaton
   * 
   */
  void Automaton::removeNonAccessibleStates(){
    assert(isValid());
    std::set <int> set_initial_state;
    for(auto const state : map_states){
      if(isStateInitial(state.first)){
        set_initial_state.insert(state.first);
      }
    }

    if(set_initial_state.empty()){
      std::multimap<int, Arc>  empty_map_arcs;
      std::map<int, State> empty_map_states;
      map_arcs = empty_map_arcs;
      map_states = empty_map_states;
      addState(0);
      setStateInitial(0);
      return;
    }

    std::set<int> visited;
    for(auto const initial_state : set_initial_state){
      depthFirstSearch_NonAccessible(initial_state, visited);
    }

    if(!visited.empty()){
      for(auto state_automate = map_states.begin(); state_automate != map_states.end(); ){
        if(visited.find(state_automate->first) == visited.end()){
          for(auto arc = map_arcs.begin(); arc != map_arcs.end(); ){
            if(arc->first == state_automate->first || arc->second.to == state_automate->first){
              arc = map_arcs.erase(arc);
            }else{
              ++arc;
            }
          }
          state_automate = map_states.erase(state_automate);
        }else{
          ++state_automate;
        }
      }
    }

  }
  /**
   * @brief Remove the non-co-accessibles states of the current automaton
   * 
   */
  void Automaton::removeNonCoAccessibleStates(){
    assert(isValid());
    std::set <int> set_final_state;
    for(auto const state : map_states){
      if(isStateFinal(state.first)){
        set_final_state.insert(state.first);
      }
    }

    if(set_final_state.empty()){
      std::multimap<int, Arc>  empty_map_arcs;
      std::map<int, State> empty_map_states;
      map_arcs = empty_map_arcs;
      map_states = empty_map_states;
      addState(0);
      setStateInitial(0);
      return;
    }

    std::set<int> visited;
    for(auto const final_state : set_final_state){
      depthFirstSearch_NonCoAccessible(final_state, visited);
    }

    if(!visited.empty()){
      for(auto state_automate = map_states.begin(); state_automate != map_states.end(); ){
        if(visited.find(state_automate->first) == visited.end()){
          for(auto arc = map_arcs.begin(); arc != map_arcs.end(); ){
            if(arc->first == state_automate->first || arc->second.to == state_automate->first){
              arc = map_arcs.erase(arc);
            }else{
              ++arc;
            }
          }
          state_automate = map_states.erase(state_automate);
        }else{
          ++state_automate;
        }
      }
    }
  }

  
  // ------------------- 7 Produit d'automate
  /**
   * @brief create a synchronized product between two automata : lhs and rhs
   * 
   * @param lhs the left hand automaton
   * @param rhs the right hand automaton
   * @return Automaton that is the product
   */
  Automaton Automaton::createProduct(const Automaton& lhs, const Automaton& rhs){
    assert(lhs.isValid());
    assert(rhs.isValid());

    Automaton product;

    for(auto const &alph_lhs : lhs.alphabet){
      for(auto const &alph_rhs : rhs.alphabet){
        if(alph_lhs == alph_rhs){
          product.addSymbol(alph_lhs);
        }
      }
    }

    std::map<std::pair<int,int>,int> product_states;
    int nb = 0;
    for(auto const &state_lhs : lhs.map_states){
      for(auto const &state_rhs : rhs.map_states){
        if(lhs.isStateInitial(state_lhs.first) && rhs.isStateInitial(state_rhs.first)){
          product_states.insert({std::make_pair(state_lhs.first,state_rhs.first),nb});
          product.addState(nb);
          product.setStateInitial(nb);
          if(lhs.isStateFinal(state_lhs.first) && rhs.isStateFinal(state_rhs.first)){
            product.setStateFinal(nb);
          }
          nb++;
        }
      }
    }

    for(auto const state : product_states){
      for(auto const alph : product.alphabet){

        std::set<int> lhs_to;
        for(auto const state_lhs : lhs.map_states){
          if(lhs.hasTransition(state.first.first, alph, state_lhs.first)){
            lhs_to.insert(state_lhs.first);
          }
        }

        std::set<int> rhs_to;
        for(auto const state_rhs : rhs.map_states){
          if(rhs.hasTransition(state.first.second, alph, state_rhs.first)){
            rhs_to.insert(state_rhs.first);
          }
        }

        for(auto const lhs_state_to : lhs_to){
          for(auto const rhs_state_to : rhs_to){
            auto key_product_state = product_states.find(std::make_pair(lhs_state_to,rhs_state_to));
            if(key_product_state != product_states.end()){
              product.addTransition(state.second, alph, key_product_state->second);
            }else{
              product_states.insert({std::make_pair(lhs_state_to,rhs_state_to),nb});
              product.addState(nb);
              product.addTransition(state.second, alph, nb);
              if(lhs.isStateFinal(lhs_state_to) && rhs.isStateFinal(rhs_state_to)){
                product.setStateFinal(nb);
              }
              nb++;
            }
          }
        }
      }
    }

    if(!product.isValid()){
      if(product.countSymbols() == 0){
        product.addSymbol('z');
      }
      if(product.countStates() == 0){
        product.addState(0);
        product.setStateInitial(0);
      }
    }

    return product;
  }

  /**
   * @brief Check if the intersection between two automata is empty or not
   * 
   * @param other the other automaton whith we will check
   * @return true if the intersection between automata is empty
   * @return false if the intersection between automata isn't empty
   */
  bool Automaton::hasEmptyIntersectionWith(const Automaton& other) const{
    assert(isValid());
    assert(other.isValid());
    
    Automaton product = createProduct(*this, other);
    return product.isLanguageEmpty();
  }

  // ------------------- 8 Lecture d'un mot

  /**
   * @brief Shows in which state(s) the word ends in
   * 
   * @param word the word that we want to know where he will end in the automaton
   * @return std::set<int> the numbers of the states if the word can be in, else an empty set
   */
  std::set<int> Automaton::readString(const std::string& word) const{
    assert(isValid());
    std::set<int> deriv;

    std::set <int> set_initial_state;
    for(auto const state : map_states){
      if(isStateInitial(state.first)){
        set_initial_state.insert(state.first);
      }
    }

    for(auto initial_state : set_initial_state){
      std::set<int> r = endStateOfWord(initial_state, word);
      std::set<int> recursiv_set = endStateOfWord(initial_state, word);
      std::set<int> merged_set;
      std::merge(deriv.begin(), deriv.end(), recursiv_set.begin(), recursiv_set.end(), std::inserter(merged_set, merged_set.end()));
      deriv = merged_set;
    }

    return deriv;
  }

  /**
   * @brief Says if the current automaton can read a word or not
   * 
   * @param word the word that we want to know if the automaton can read it
   * @return true if the automaton can read the word in parameter
   * @return false if the automaton cannot read the word in parameter
   */
  bool Automaton::match(const std::string& word) const{
    std::set<int> deriv = readString(word);
    for(auto state : deriv){
      if(isStateFinal(state)){
        return true;
      }
    }
    return false;
  }

  // ------------------- 9 Determinisation d'un automate

  /**
   * @brief Create a deterministic Automaton if it is not already
   * 
   * @param other the Automaton that we will use to create his deterministic version
   * @return a deterministic Automaton
   */
  Automaton Automaton::createDeterministic(const Automaton& other){
    assert(other.isValid());
    if(other.isDeterministic()){
      return other;
    }

    Automaton deterministicAutomaton;
    deterministicAutomaton.alphabet = other.alphabet;

    std::map<int,std::set<int>> deterministic_states;
    std::set<int> initial_deterministic_state;

    int nb = 0;

    // Initial State of the deterministic Automaton
    for(auto const state : other.map_states){
      if(other.isStateInitial(state.first)){
        initial_deterministic_state.insert(state.first);
      }
    }
    deterministic_states.insert({nb,initial_deterministic_state});
    deterministicAutomaton.addState(nb);
    deterministicAutomaton.setStateInitial(nb);
    for(auto const state : initial_deterministic_state){
      if(other.isStateFinal(state)){
        deterministicAutomaton.setStateFinal(nb);
      }
    }

    nb++;

    // Rest of the states of the deterministic Automaton
    for(auto const state_det : deterministic_states){
      for(auto const alph : deterministicAutomaton.alphabet){
        // On créer le tableau a insérer dans la map deterministic_states pour pouvoir parcourir ses noeuds et voir les transitions
        std::set<int> set_alph;
        // On Ajoute dans ce tableau les transitions que notre automate ancien automate allait, pour avoir les nouvels états
        for(auto const state : state_det.second){
          for(auto const arc : other.map_arcs){
            if(arc.first == state && arc.second.alpha == alph){
              set_alph.insert(arc.second.to);
            }
          }
        }
        if(set_alph.size() > 0){
          // On créer cette variable booléenne pour faire l'une des deux vérifications
          bool isPassed = false;
          for(auto const state_det_v2 : deterministic_states){
            if(state_det_v2.second == set_alph){
              deterministicAutomaton.addTransition(state_det.first, alph, state_det_v2.first);
              isPassed = true;
            }
          }
          if(!isPassed){
            deterministicAutomaton.addState(nb);
            for(auto const state : set_alph){
              if(other.isStateFinal(state)){
                deterministicAutomaton.setStateFinal(nb);
              }
            }
            deterministicAutomaton.addTransition(state_det.first, alph, nb);
            deterministic_states.insert({nb,set_alph});
            nb++;
          }
        }
      }
    }

    if(!deterministicAutomaton.isValid()){
      Automaton emptyAutomaton;
      deterministicAutomaton = emptyAutomaton;
      deterministicAutomaton.addSymbol('z');
      deterministicAutomaton.addState(0);
      deterministicAutomaton.setStateInitial(0);
    }

    return deterministicAutomaton;
  }

  /**
   * @brief Check if the current automaton language is included in the other automaton language
   * 
   * @param other the other automaton whith we will check
   * @return true if the current automaton language is included in the other automaton language
   * @return false if the current automaton language is included in the other automaton language
   */
  bool Automaton::isIncludedIn(const Automaton& other) const{
    // if(A isIncludedIn B <==> A hasEmptyIntersectionWith b.createComplement)
    assert(other.isValid());
    Automaton copyOther = other;
    for(auto const alph : alphabet){
      if(!copyOther.hasSymbol(alph)){
        copyOther.addSymbol(alph);
      }
    }
    Automaton otherComplement = createComplement(copyOther);
    return hasEmptyIntersectionWith(otherComplement);
  }

  // ------------------- 10 Minimisation d'un automate
  /**
   * @brief Create a automaton deterministic and complete and then, reduce the number of state of this one if it's possible
   * 
   * @param other the automaton that will serve to create a minimal Automaton
   * @return A minimal Automaton thanks to Moore algorithm 
   */
  Automaton Automaton::createMinimalMoore(const Automaton& other){
    assert(other.isValid());

    Automaton minimalAutomaton;
    minimalAutomaton = createDeterministic(other);
    minimalAutomaton = createComplete(minimalAutomaton);

    struct Moore{ 
      int congruenceFrom;
      std::vector<int> transitions;
      int congruenceTo; 
    };

    std::map<int, Moore> classes;

    // Congruence 0 de l'algorithme de Moore, on met les etats non finaux a la classe 1 et ceux finaux a la classe 2;
    for(auto const state : minimalAutomaton.map_states){
      struct Moore st;
      if(minimalAutomaton.isStateFinal(state.first)){
        st.congruenceFrom = 2;
      }else{
        st.congruenceFrom = 1;
      }
      classes.insert({state.first, st});
    }

    bool areSames;  //Variable premettant d'arreter le do while CongruenceFrom = CongruenceTo ?
    do{

      for(auto &itera : classes){
        itera.second.transitions.clear();
      }

      areSames = true;

      for(auto const alpha : minimalAutomaton.alphabet){
        for(auto const transition : minimalAutomaton.map_arcs){
          if(transition.second.alpha == alpha){ 
            classes[transition.first].transitions.push_back(classes[transition.second.to].congruenceFrom);
          }
        }
      }

      int numero_classe = 1;
      for(std::map<int, Moore>::iterator iterator = classes.begin(); iterator != classes.end(); iterator++){
        bool isPassed = false;
        for(std::map<int, Moore>::iterator checking = classes.begin(); checking != iterator; checking++){
          if(checking->second.congruenceFrom == iterator->second.congruenceFrom && checking->second.transitions == iterator->second.transitions){
            iterator->second.congruenceTo = checking->second.congruenceTo;
            isPassed = true;
            break;
          }
        }
        if(!isPassed){
          iterator->second.congruenceTo = numero_classe;
          numero_classe++;
        }
      }

      // On vérifie si la congruence précédente et la suivante (ou actuelle) sont les mêmes, si oui, l'automate est minimal, on arrête donc d'itérer
      for(auto &it : classes){
        if(it.second.congruenceFrom != it.second.congruenceTo){
          it.second.congruenceFrom = it.second.congruenceTo;
          areSames = false;
        }
      }
    }while(!areSames);

    // Contruction de l'automate minimal Moore
    Automaton minimalAutomatonMoore;
    // > Alphabet
    minimalAutomatonMoore.alphabet = minimalAutomaton.alphabet;
    // > Les etats
    for(auto const st : classes){
      minimalAutomatonMoore.addState(st.second.congruenceFrom);
      if(minimalAutomaton.isStateInitial(st.first)){
        minimalAutomatonMoore.setStateInitial(st.second.congruenceFrom);
      }
      if(minimalAutomaton.isStateFinal(st.first)){
        minimalAutomatonMoore.setStateFinal(st.second.congruenceFrom);
      }
    }
    // > Les transitions
    int i = 0;
    for(auto const alpha : minimalAutomatonMoore.alphabet){
      for(auto const tr : classes){
        minimalAutomatonMoore.addTransition(tr.second.congruenceFrom, alpha, tr.second.transitions[i]);
      }
      i++;
    }

    return minimalAutomatonMoore;
  }

    /**
   * @brief Create a automaton deterministic and complete and then, reduce the number of state of this one if it's possible
   * 
   * @param other the automaton that will serve to create a minimal Automaton
   * @return A minimal Automaton thanks to Brzozowski algorithm 
   */
  Automaton Automaton::createMinimalBrzozowski(const Automaton& other){
    assert(other.isValid());

    // Brzozowski -> CreateDeterministe(CreateMirror(CreateDeterministic(CreateMirror(other))));

    Automaton minimalAutomaton = fa::Automaton::createMirror(other);
    minimalAutomaton = fa::Automaton::createDeterministic(minimalAutomaton);

    minimalAutomaton = fa::Automaton::createMirror(minimalAutomaton);
    minimalAutomaton = fa::Automaton::createDeterministic(minimalAutomaton);

    minimalAutomaton = fa::Automaton::createComplete(minimalAutomaton);

    return minimalAutomaton;
   }
}