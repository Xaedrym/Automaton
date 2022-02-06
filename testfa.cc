#include "gtest/gtest.h"
#include "Automaton.h"

// Test if the automaton is valid
TEST(AutomatonExampleTest, Default) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.isValid());
}

// TESTS ON SYMBOLS

// -------------------------------------------------------------------- AddSymbol

TEST(AutomatonAddSymbolTest, AddSymbolC) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addSymbol('a'));
}

TEST(AutomatonAddSymbolTest, AddSymbolEpsilon) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\0'));
  EXPECT_FALSE(fa.addSymbol(fa::Epsilon));
}

TEST(AutomatonAddSymbolTest, AddSymbolNotPrintable) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addSymbol('\n'));
  EXPECT_FALSE(fa.addSymbol('\t'));
}

// -------------------------------------------------------------------- RemoveSymbol

TEST(AutomatonRemoveSymbolTest, RemoveSymbolExisting) {
  fa::Automaton fa;
  fa.addSymbol('c');
  EXPECT_TRUE(fa.removeSymbol('c'));
}

TEST(AutomatonRemoveSymbolTest, RemoveSymbolExistingWithTransitions) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addSymbol('a');

  fa.addState(0);
  fa.addState(1);

  fa.addTransition(0,'a',1);
  fa.addTransition(1,'c',0);

  EXPECT_EQ(2u, fa.countTransitions());
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_FALSE(fa.hasTransition(1,'c',0));
  EXPECT_EQ(1u, fa.countTransitions());
}

TEST(AutomatonRemoveSymbolTest, RemoveSymbolExistingWithMoreTransitions) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addSymbol('a');

  fa.addState(0);
  fa.addState(1);

  fa.addTransition(0,'a',1);
  fa.addTransition(0,'c',0);
  fa.addTransition(0,'c',1);
  fa.addTransition(1,'c',0);
  fa.addTransition(1,'c',1);

  EXPECT_EQ(5u, fa.countTransitions());
  EXPECT_TRUE(fa.removeSymbol('c'));
  EXPECT_FALSE(fa.hasTransition(0,'c',0));
  EXPECT_FALSE(fa.hasTransition(0,'c',1));
  EXPECT_FALSE(fa.hasTransition(1,'c',0));
  EXPECT_FALSE(fa.hasTransition(1,'c',1));
  EXPECT_EQ(1u, fa.countTransitions());
}

TEST(AutomatonRemoveSymbolTest, RemoveSymbolNotExisting) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeSymbol('c'));
}

// -------------------------------------------------------------------- HasSymbol

TEST(AutomatonHasSymbolTest, HasSymbolC) {
  fa::Automaton fa;
  fa.addSymbol('c');
  EXPECT_TRUE(fa.hasSymbol('c'));
}

TEST(AutomatonHasSymbolTest, HasNotSymbolC) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('c'));
}

// -------------------------------------------------------------------- CountSymbol

TEST(AutomatonCountSymbol, CountSymbol0) {
  fa::Automaton fa;
  EXPECT_EQ(0u,fa.countSymbols());
}

TEST(AutomatonCountSymbol, CountSymbol1) {
  fa::Automaton fa;
  fa.addSymbol('c');
  EXPECT_EQ(1u,fa.countSymbols());
}

TEST(AutomatonCountSymbol, CountSymbol3) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  EXPECT_EQ(3u,fa.countSymbols());
}


// TESTS SUR LES STATES

// -------------------------------------------------------------------- AddState

TEST(AutomatonAddStateTest, AddState1) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(1));
}

TEST(AutomatonAddStateTest, AddState0) {
  fa::Automaton fa;
  EXPECT_TRUE(fa.addState(0));
}

TEST(AutomatonAddStateTest, AddStateNegatif1) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.addState(-1));
}

// -------------------------------------------------------------------- RemoveState

TEST(AutomatonRemoveStateTest, RemoveStateExisting) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.removeState(1));
}

TEST(AutomatonRemoveStateTest, RemoveStateNotExisting) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.removeState(1));
}

TEST(AutomatonRemoveStateTest, RemoveStateExistingWithTransitions) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addSymbol('a');

  fa.addState(0);
  fa.addState(1);
  fa.addState(2);

  fa.addTransition(0,'a',1);
  fa.addTransition(1,'c',0);
  fa.addTransition(1,'a',2);

  EXPECT_EQ(3u, fa.countTransitions());
  EXPECT_TRUE(fa.removeState(2));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(2u, fa.countTransitions());
}

TEST(AutomatonRemoveStateTest, RemoveStateExistingWithTransitionsV2) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addSymbol('a');

  fa.addState(0);
  fa.addState(1);
  fa.addState(2);

  fa.addTransition(0,'a',1);
  fa.addTransition(1,'c',0);
  fa.addTransition(1,'a',2);

  EXPECT_EQ(3u, fa.countTransitions());
  EXPECT_TRUE(fa.removeState(1));
  EXPECT_FALSE(fa.hasTransition(0,'a',1));
  EXPECT_FALSE(fa.hasTransition(1,'c',0));
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_EQ(0u, fa.countTransitions());
}

// -------------------------------------------------------------------- HasState

TEST(AutomatonHasStateTest, HasState1) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_TRUE(fa.hasState(1));
}

TEST(AutomatonHasStateTest, HasState0) {
  fa::Automaton fa;
  fa.addState(0);
  EXPECT_TRUE(fa.hasState(0));
}

TEST(AutomatonHasStateTest, HasNotState1) {
  fa::Automaton fa;
  EXPECT_FALSE(fa.hasSymbol('c'));
}

// -------------------------------------------------------------------- CountState

TEST(AutomatonCountState, CountState0) {
  fa::Automaton fa;
  EXPECT_EQ(0u,fa.countStates());
}

TEST(AutomatonCountState, CountState1) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_EQ(1u,fa.countStates());
}

TEST(AutomatonCountState, CountState3) {
  fa::Automaton fa;
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  EXPECT_EQ(3u,fa.countStates());
}

// -------------------------------------------------------------------- isStateInitial

TEST(AutomatonIsStateInitial, IsStateInitialYes) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateInitial(1));
}

TEST(AutomatonIsStateInitial, IsStateInitialNot) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateInitial(1);
  EXPECT_TRUE(fa.isStateInitial(1));
}

// -------------------------------------------------------------------- IsStateFinal

TEST(AutomatonIsStateFinal, IsStateFinalNo) {
  fa::Automaton fa;
  fa.addState(1);
  EXPECT_FALSE(fa.isStateFinal(1));
}

TEST(AutomatonIsStateFinal, IsStateFinalYes) {
  fa::Automaton fa;
  fa.addState(1);
  fa.setStateFinal(1);
  EXPECT_TRUE(fa.isStateFinal(1));
}

// TESTS SUR LES TRANSITIONS 

// -------------------------------------------------------------------- AddTransition

TEST(AutomatonAddTransitionTest, AddTransitionSucceed) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  EXPECT_TRUE(fa.addTransition(1,'c',2));
}

TEST(AutomatonAddTransitionTest, AddTransitionFailedAlpha) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(1);
  fa.addState(2);
  EXPECT_FALSE(fa.addTransition(1,'c',2));
}

TEST(AutomatonAddTransitionTest, AddTransitionFailedState) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(3);
  EXPECT_FALSE(fa.addTransition(1,'c',2));
}

TEST(AutomatonAddTransitionTest, AddTransitionFailedAlreadyAdded) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  EXPECT_FALSE(fa.addTransition(1,'c',2));
}

TEST(AutomatonAddTransitionTest, AddEpsilonTransition) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  EXPECT_TRUE(fa.addTransition(1,fa::Epsilon,2));
}

// -------------------------------------------------------------------- RemoveTransition

TEST(AutomatonRemoveTransitionTest, RemoveTransitionSucceed) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  EXPECT_TRUE(fa.removeTransition(1,'c',2));
  EXPECT_FALSE(fa.hasTransition(1,'c',2));
}

TEST(AutomatonRemoveTransitionTest, RemoveTransitionFailedSymbolRemove) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  EXPECT_FALSE(fa.removeTransition(1,'b',2));
  EXPECT_TRUE(fa.hasTransition(1,'c',2));
  EXPECT_FALSE(fa.hasTransition(1,'b',2));
}

TEST(AutomatonRemoveTransitionTest, RemoveTransitionFailedSymbolAdd) {
  fa::Automaton fa;
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  EXPECT_FALSE(fa.removeTransition(1,'b',2));
  EXPECT_FALSE(fa.hasTransition(1,'c',2));
  EXPECT_FALSE(fa.hasTransition(1,'b',2));
}

TEST(AutomatonRemoveTransitionTest, RemoveTransitionFailedState) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  EXPECT_FALSE(fa.removeTransition(1,'c',3));
  EXPECT_TRUE(fa.hasTransition(1,'c',2));
  EXPECT_FALSE(fa.hasTransition(1,'c',3));
}

TEST(AutomatonRemoveTransitionTest, OneTransitionLeft) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  fa.addTransition(1,'b',2);
  EXPECT_TRUE(fa.removeTransition(1,'c',2));
  EXPECT_FALSE(fa.hasTransition(1,'c',2));
  EXPECT_TRUE(fa.hasTransition(1,'b',2));
  EXPECT_EQ(1u,fa.countTransitions());
}

// -------------------------------------------------------------------- HasTransition

TEST(AutomatonHasTransitionTest, HasTransitionSucceed) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'c',2);
  EXPECT_TRUE(fa.hasTransition(1,'c',2));
}

TEST(AutomatonHasTransitionTest, HasTransitionFailedAlpha) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addState(1);
  fa.addState(2);
  fa.addTransition(1,'a',2);
  EXPECT_FALSE(fa.hasTransition(1,'c',2));
}

TEST(AutomatonHasTransitionTest, HasTransitionFailedState) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(3);
  fa.addTransition(1,'c',3);
  EXPECT_FALSE(fa.hasTransition(1,'c',2));
}

TEST(AutomatonHasTransitionTest, HasTransitionFailedState2) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(3);
  fa.addTransition(1,'c',1);
  fa.addTransition(1,'c',3);
  EXPECT_TRUE(fa.hasTransition(1,'c',1));
  EXPECT_FALSE(fa.hasTransition(1,'b',1));
}

// -------------------------------------------------------------------- CountTransition

TEST(AutomatonCountTransition, CountTransition0) {
  fa::Automaton fa;
  EXPECT_EQ(0u,fa.countTransitions());
}

TEST(AutomatonCountTransition, CountTransition1) {
  fa::Automaton fa;
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  EXPECT_TRUE(fa.addTransition(1,'c',2));
  EXPECT_EQ(1u,fa.countTransitions());
}

TEST(AutomatonCountTranstion, CountTransition3) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(3,'c',2));
  EXPECT_TRUE(fa.addTransition(4,'c',2));
  EXPECT_EQ(4u,fa.countTransitions());
}

TEST(AutomatonCountTranstion, CountTransition4) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_EQ(4u,fa.countTransitions());
}

// -------------------------------------------------------------------- HasEpsilonTransition

TEST(AutomatonHasEpsilonTransition, HasEpsilonTransitionFailed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_EQ(4u,fa.countTransitions());
  EXPECT_FALSE(fa.hasEpsilonTransition());
}

TEST(AutomatonHasEpsilonTransition, HasEpsilonTransitionSucceed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_TRUE(fa.addTransition(1,fa::Epsilon,2));
  EXPECT_EQ(5u,fa.countTransitions());
  EXPECT_TRUE(fa.hasEpsilonTransition());
}

// -------------------------------------------------------------------- IsDeterministic

TEST(AutomatonIsDeterministic, IsDeterministicFailed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_FALSE(fa.isDeterministic());
}

TEST(AutomatonIsDeterministic, IsDeterministicSucceed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_TRUE(fa.isDeterministic());
}

// -------------------------------------------------------------------- IsComplete

TEST(AutomatonIsComplete, IsCompleteFailed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isComplete());
}

TEST(AutomatonIsComplete, IsCompleteSucceed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'c',2));

  EXPECT_TRUE(fa.addTransition(2,'a',1));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  
  EXPECT_TRUE(fa.isComplete());
}

// -------------------------------------------------------------------- CreateComplete

TEST(AutomatonCreateComplete, CreateCompleteAlreadyCompleted) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'c',2));

  EXPECT_TRUE(fa.addTransition(2,'a',1));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  
  EXPECT_TRUE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),2u);

  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_FALSE(fa.match("cc"));
  EXPECT_TRUE(fa.match("ab"));
  EXPECT_TRUE(fa.match("aaaaaaaabbbbbbbbbbbb"));
  EXPECT_TRUE(fa.match("c"));
  EXPECT_TRUE(fa.match("ccc"));

  fa::Automaton complete = fa.createComplete(fa);
  EXPECT_TRUE(complete.isComplete());
  EXPECT_TRUE(complete.isValid());
  EXPECT_EQ(complete.countStates(),2u);


  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(complete.match("a"));
  EXPECT_FALSE(complete.match("aa"));
  EXPECT_FALSE(complete.match("aba"));
  EXPECT_FALSE(complete.match("cc"));
  EXPECT_TRUE(complete.match("ab"));
  EXPECT_TRUE(complete.match("aaaaaaaabbbbbbbbbbbb"));
  EXPECT_TRUE(complete.match("c"));
  EXPECT_TRUE(complete.match("ccc"));
}

TEST(AutomatonCreateComplete, CreateCompleteSucceed) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),2u);

  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccca"));

  fa::Automaton complete = fa.createComplete(fa);
  EXPECT_TRUE(complete.isComplete());
  EXPECT_TRUE(complete.isValid());
  EXPECT_EQ(complete.countStates(),3u);


  EXPECT_FALSE(complete.match("c"));
  EXPECT_FALSE(complete.match("b"));
  EXPECT_FALSE(complete.match(""));
  EXPECT_FALSE(complete.match("aa"));
  EXPECT_TRUE(complete.match("a"));
  EXPECT_TRUE(complete.match("ac"));
  EXPECT_TRUE(complete.match("abbb"));
  EXPECT_TRUE(complete.match("accccccc"));
  EXPECT_TRUE(complete.match("acacaccca"));
}

TEST(AutomatonCreateComplete, ROLLET_MAX_INT) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(INT_MAX);
  fa.setStateInitial(1);
  fa.setStateFinal(INT_MAX);
  EXPECT_TRUE(fa.addTransition(1,'a',INT_MAX));

  EXPECT_TRUE(fa.addTransition(INT_MAX,'b',INT_MAX));
  EXPECT_TRUE(fa.addTransition(INT_MAX,'c',INT_MAX));
  EXPECT_TRUE(fa.addTransition(INT_MAX,'c',1));

  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),2u);

  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccca"));

  fa::Automaton complete = fa.createComplete(fa);
  EXPECT_TRUE(complete.isComplete());
  EXPECT_TRUE(complete.isValid());
  EXPECT_EQ(complete.countStates(),3u);

  EXPECT_FALSE(complete.match("c"));
  EXPECT_FALSE(complete.match("b"));
  EXPECT_FALSE(complete.match(""));
  EXPECT_FALSE(complete.match("aa"));
  EXPECT_TRUE(complete.match("a"));
  EXPECT_TRUE(complete.match("ac"));
  EXPECT_TRUE(complete.match("abbb"));
  EXPECT_TRUE(complete.match("accccccc"));
  EXPECT_TRUE(complete.match("acacaccca"));
}

TEST(AutomatonCreateComplete, CreateCompleteSucceedStateLongAfter) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'c',3));
  EXPECT_TRUE(fa.addTransition(1,'c',5));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),4u);

  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccca"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton complete = fa.createComplete(fa);
  EXPECT_TRUE(complete.isComplete());
  EXPECT_TRUE(complete.isValid());
  EXPECT_EQ(complete.countStates(),5u);

  EXPECT_FALSE(complete.match("c"));
  EXPECT_FALSE(complete.match("b"));
  EXPECT_FALSE(complete.match(""));
  EXPECT_FALSE(complete.match("aa"));
  EXPECT_TRUE(complete.match("a"));
  EXPECT_TRUE(complete.match("ac"));
  EXPECT_TRUE(complete.match("abbb"));
  EXPECT_TRUE(complete.match("accccccc"));
  EXPECT_TRUE(complete.match("acacaccca"));
  EXPECT_TRUE(complete.match("acabbbbcac"));
}

TEST(AutomatonCreateComplete, NotCreatingNewStateForBin) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_EQ(fa.countStates(),1u);

  fa::Automaton complete = fa.createComplete(fa);
  EXPECT_TRUE(complete.isComplete());
  EXPECT_TRUE(complete.isValid());
  EXPECT_EQ(complete.countStates(),1u);

  EXPECT_FALSE(complete.match("a"));
  EXPECT_FALSE(complete.match("b"));
  EXPECT_FALSE(complete.match("aa"));
  EXPECT_FALSE(complete.match(""));
}



// -------------------------------------------------------------------- CreateComplement

TEST(AutomatonCreateComplement, AlreadyCompleteAndDeterministic) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'c',2));

  EXPECT_TRUE(fa.addTransition(2,'a',1));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.isComplete());

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("cc"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("c"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccc"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton complement = fa.createComplement(fa);
  EXPECT_TRUE(complement.isValid());
  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());

  EXPECT_TRUE(complement.match("a"));
  EXPECT_TRUE(complement.match("cc"));
  EXPECT_TRUE(complement.match(""));
  EXPECT_TRUE(complement.match("aa"));
  EXPECT_FALSE(complement.match("b"));
  EXPECT_FALSE(complement.match("c"));
  EXPECT_FALSE(complement.match("ac"));
  EXPECT_FALSE(complement.match("abbb"));
  EXPECT_FALSE(complement.match("accccccc"));
  EXPECT_FALSE(complement.match("acacaccc"));
  EXPECT_FALSE(complement.match("acabbbbcac"));
}

TEST(AutomatonCreateComplement, NoCompleteAndNoDeterministic) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'c',3));
  EXPECT_TRUE(fa.addTransition(1,'c',5));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_FALSE(fa.isComplete());

  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccca"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton complement = fa.createComplement(fa);
  EXPECT_TRUE(complement.isValid());
  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());

  EXPECT_TRUE(complement.match("c"));
  EXPECT_TRUE(complement.match("b"));
  EXPECT_TRUE(complement.match(""));
  EXPECT_TRUE(complement.match("aa"));
  EXPECT_FALSE(complement.match("a"));
  EXPECT_FALSE(complement.match("ac"));
  EXPECT_FALSE(complement.match("abbb"));
  EXPECT_FALSE(complement.match("accccccc"));
  EXPECT_FALSE(complement.match("acacaccca"));
  EXPECT_FALSE(complement.match("acabbbbcac"));
}

TEST(AutomatonCreateComplement, ComplementTwoTimes) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));
  EXPECT_TRUE(fa.addTransition(1,'c',3));
  EXPECT_TRUE(fa.addTransition(1,'c',5));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_FALSE(fa.isComplete());

  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccca"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton complement = fa.createComplement(fa);
  EXPECT_TRUE(complement.isValid());
  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());

  EXPECT_TRUE(complement.match("c"));
  EXPECT_TRUE(complement.match("b"));
  EXPECT_TRUE(complement.match(""));
  EXPECT_TRUE(complement.match("aa"));
  EXPECT_FALSE(complement.match("a"));
  EXPECT_FALSE(complement.match("ac"));
  EXPECT_FALSE(complement.match("abbb"));
  EXPECT_FALSE(complement.match("accccccc"));
  EXPECT_FALSE(complement.match("acacaccca"));
  EXPECT_FALSE(complement.match("acabbbbcac"));

  fa::Automaton complement_bis = fa.createComplement(complement);
  EXPECT_TRUE(complement_bis.isValid());
  EXPECT_TRUE(complement_bis.isDeterministic());
  EXPECT_TRUE(complement_bis.isComplete());

  EXPECT_FALSE(complement_bis.match("c"));
  EXPECT_FALSE(complement_bis.match("b"));
  EXPECT_FALSE(complement_bis.match(""));
  EXPECT_FALSE(complement_bis.match("aa"));
  EXPECT_TRUE(complement_bis.match("a"));
  EXPECT_TRUE(complement_bis.match("ac"));
  EXPECT_TRUE(complement_bis.match("abbb"));
  EXPECT_TRUE(complement_bis.match("accccccc"));
  EXPECT_TRUE(complement_bis.match("acacaccca"));
  EXPECT_TRUE(complement_bis.match("acabbbbcac"));
}

TEST(AutomatonCreateComplement, NoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match(""));

  fa::Automaton complement = fa.createComplement(fa);
  EXPECT_TRUE(complement.isValid());
  EXPECT_TRUE(complement.isDeterministic());
  EXPECT_TRUE(complement.isComplete());

  EXPECT_TRUE(complement.match("a"));
  EXPECT_TRUE(complement.match("b"));
  EXPECT_TRUE(complement.match("aa"));
  EXPECT_TRUE(complement.match(""));
  EXPECT_TRUE(complement.isValid());
}


// -------------------------------------------------------------------- CreateMirror

TEST(AutomatonCreateMirror, CreateMirrorAndIsCompleted) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',1));
  EXPECT_TRUE(fa.addTransition(1,'b',2));
  EXPECT_TRUE(fa.addTransition(1,'c',2));

  EXPECT_TRUE(fa.addTransition(2,'a',1));
  EXPECT_TRUE(fa.addTransition(2,'c',1));
  EXPECT_TRUE(fa.addTransition(2,'b',2));
  
  EXPECT_TRUE(fa.isComplete());

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("cc"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("c"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccc"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton mirror = fa.createMirror(fa);
  EXPECT_TRUE(mirror.isValid());

  EXPECT_FALSE(mirror.match("a"));
  EXPECT_FALSE(mirror.match("cc"));
  EXPECT_FALSE(mirror.match(""));
  EXPECT_FALSE(mirror.match("aa"));
  EXPECT_TRUE(mirror.match("b"));
  EXPECT_TRUE(mirror.match("c"));
  EXPECT_TRUE(mirror.match("ca"));
  EXPECT_TRUE(mirror.match("bbba"));
  EXPECT_TRUE(mirror.match("ccccccca"));
  EXPECT_TRUE(mirror.match("cccacaca"));
  EXPECT_TRUE(mirror.match("cacbbbbaca"));
}

TEST(AutomatonCreateMirror, CreateMirrorNotCompleted) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isComplete());

  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("abc"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccc"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton mirror = fa.createMirror(fa);
  EXPECT_TRUE(mirror.isValid());

  EXPECT_FALSE(mirror.match("b"));
  EXPECT_FALSE(mirror.match("c"));
  EXPECT_FALSE(mirror.match(""));
  EXPECT_FALSE(mirror.match("aa"));
  EXPECT_TRUE(mirror.match("a"));
  EXPECT_TRUE(mirror.match("cba"));
  EXPECT_TRUE(mirror.match("ca"));
  EXPECT_TRUE(mirror.match("bbba"));
  EXPECT_TRUE(mirror.match("ccccccca"));
  EXPECT_TRUE(mirror.match("cccacaca"));
  EXPECT_TRUE(mirror.match("cacbbbbaca"));
}

TEST(AutomatonCreateMirror, CreateMirrorInitialsAreFinalsTo) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(2);
  EXPECT_TRUE(fa.addTransition(1,'a',2));

  EXPECT_TRUE(fa.addTransition(2,'b',2));
  EXPECT_TRUE(fa.addTransition(2,'c',2));
  EXPECT_TRUE(fa.addTransition(2,'c',1));

  EXPECT_FALSE(fa.isComplete());

  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("abc"));
  EXPECT_TRUE(fa.match("ac"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("accccccc"));
  EXPECT_TRUE(fa.match("acacaccc"));
  EXPECT_TRUE(fa.match("acabbbbcac"));

  fa::Automaton mirror = fa.createMirror(fa);
  EXPECT_TRUE(mirror.isValid());

  EXPECT_FALSE(mirror.match("b"));
  EXPECT_FALSE(mirror.match("c"));
  EXPECT_FALSE(mirror.match("aa"));
  EXPECT_TRUE(mirror.match(""));
  EXPECT_TRUE(mirror.match("a"));
  EXPECT_TRUE(mirror.match("cba"));
  EXPECT_TRUE(mirror.match("ca"));
  EXPECT_TRUE(mirror.match("bbba"));
  EXPECT_TRUE(mirror.match("ccccccca"));
  EXPECT_TRUE(mirror.match("cccacaca"));
  EXPECT_TRUE(mirror.match("cacbbbbaca"));
}

// -------------------------------------------------------------------- IsLanguageEmpty

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyNoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);

  fa.setStateFinal(2);

  fa.addTransition(1,'a',2);

  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',2);
  fa.addTransition(2,'c',1);

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyNoFinalState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');
  fa.addState(1);
  fa.addState(2);
  fa.setStateInitial(1);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',2);
  fa.addTransition(2,'c',1);

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyTrue) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);
  
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',2);
  fa.addTransition(2,'c',2);
  fa.addTransition(2,'b',1);
  fa.addTransition(3,'a',1);

  EXPECT_TRUE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyFalse) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyFalseInitialStateIsFinal) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(1);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyFalseMultipleInitial) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',1);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  EXPECT_FALSE(fa.isLanguageEmpty());
}

TEST(AutomatonIsLanguageEmpty, IsLanguageEmptyWord) {
  fa::Automaton fa;
  fa.addSymbol('a');

  fa.addState(1);

  fa.setStateInitial(1);
  fa.setStateFinal(1);

  EXPECT_FALSE(fa.isLanguageEmpty());
}


TEST(AutomatonIsLanguageEmpty, NonDeterministicTest) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',2);
  lhs.addTransition(1,'b',3);
  lhs.addTransition(2,'a',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'b',2);
  rhs.addTransition(2,'a',1);
  rhs.addTransition(2,'a',3);
  rhs.addTransition(3,'b',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(5u,product.countStates());
  EXPECT_EQ(4u,product.countTransitions());
  EXPECT_TRUE(product.isValid());

  EXPECT_FALSE(product.isLanguageEmpty());
}

// -------------------------------------------------------------------- Non Accessible -----------------------/

TEST(AutomatonRemoveNonAccessibleStates, NoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateFinal(3);

  fa.addTransition(1,'a',1);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  fa.removeNonAccessibleStates();
  EXPECT_EQ(1u,fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonAccessibleStates, HasOnlyAccessibleState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  fa.removeNonAccessibleStates();
  EXPECT_EQ(3u,fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonAccessibleStates, LastStateNonAccessible) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  fa.removeNonAccessibleStates();
  EXPECT_EQ(2u,fa.countStates());
  EXPECT_EQ(3u,fa.countTransitions());
  EXPECT_FALSE(fa.hasTransition(3,'a',1));
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonAccessibleStates, NonAccessibleEnChaine) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);

  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',3);
  fa.addTransition(3,'c',3);
  fa.addTransition(4,'a',5);

  fa.removeNonAccessibleStates();
  EXPECT_EQ(3u,fa.countStates());
  EXPECT_EQ(3u,fa.countTransitions());
  EXPECT_FALSE(fa.hasTransition(4,'a',5));
  EXPECT_FALSE(fa.hasState(4));
  EXPECT_FALSE(fa.hasState(5));
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonAccessibleStates, NonAccessibleOnlyState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',1);

  fa.removeNonAccessibleStates();
  EXPECT_EQ(2u,fa.countStates());
  EXPECT_EQ(2u,fa.countTransitions());
  EXPECT_FALSE(fa.hasState(3));
  EXPECT_TRUE(fa.isValid());
}

// -------------------------------------------------------------------- Non Co Assessible ------------------------------//

TEST(AutomatonRemoveNonCoAccessibleStates, NoFinalState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);

  fa.addTransition(1,'a',1);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(1u,fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonCoAccessibleStates, HasOnlyCoAccessibleState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(2,'c',1);
  fa.addTransition(3,'a',1);

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(3u,fa.countStates());
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonCoAccessibleStates, FirstStateNonCoAccessible) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(1,'a',1);
  fa.addTransition(2,'b',2);
  fa.addTransition(2,'c',3);
  fa.addTransition(3,'a',1);

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(2u,fa.countStates());
  EXPECT_EQ(2u,fa.countTransitions());
  EXPECT_FALSE(fa.hasTransition(1,'a',1));
  EXPECT_FALSE(fa.addTransition(3,'a',1));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonCoAccessibleStates, NonCoAccessibleEnChaine) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);

  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.setStateFinal(5);

  fa.addTransition(1,'a',2);
  fa.addTransition(2,'b',2);
  fa.addTransition(3,'c',4);
  fa.addTransition(4,'a',5);

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(3u,fa.countStates());
  EXPECT_EQ(2u,fa.countTransitions());
  EXPECT_FALSE(fa.hasTransition(1,'a',2));
  EXPECT_FALSE(fa.hasTransition(2,'b',2));
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_FALSE(fa.hasState(2));
  EXPECT_TRUE(fa.isValid());
}

TEST(AutomatonRemoveNonCoAccessibleStates, NonCoAccessibleOnlyState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);

  fa.setStateInitial(1);
  fa.setStateFinal(3);

  fa.addTransition(3,'a',3);
  fa.addTransition(2,'b',3);

  fa.removeNonCoAccessibleStates();
  EXPECT_EQ(2u,fa.countStates());
  EXPECT_EQ(2u,fa.countTransitions());
  EXPECT_FALSE(fa.hasState(1));
  EXPECT_TRUE(fa.isValid());
}

// -------------------------------------------------------------------- 7 Produit d'automate

TEST(AutomatonCreateProduct, NonDeterministicAndSamesAutomatons) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'a',3);
  rhs.addTransition(1,'a',2);
  rhs.addTransition(1,'b',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(5u,product.countStates());
  EXPECT_EQ(5u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_TRUE(product.match("b"));
  EXPECT_TRUE(product.match("a"));
  EXPECT_FALSE(product.match(""));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, NonDeterministicAndSameAutomata) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton product = product.createProduct(fa,fa);
  EXPECT_EQ(5u,product.countStates());
  EXPECT_EQ(5u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_TRUE(product.match("b"));
  EXPECT_TRUE(product.match("a"));
  EXPECT_FALSE(product.match(""));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, EmptyProduct) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);
  EXPECT_FALSE(lhs.match(""));


  fa::Automaton rhs;
  rhs.addSymbol('c');
  rhs.addSymbol('d');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'d',2);
  rhs.addTransition(1,'d',3);
  EXPECT_FALSE(rhs.match(""));


  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(1u,product.countStates());
  EXPECT_EQ(0u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_TRUE(product.isLanguageEmpty());

  EXPECT_FALSE(product.match("d"));
  EXPECT_FALSE(product.match("c"));
  EXPECT_FALSE(product.match("b"));
  EXPECT_FALSE(product.match("a"));
  EXPECT_FALSE(product.match(""));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, EmptyProductbutMatchEmptyWord) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);
  EXPECT_TRUE(lhs.match(""));


  fa::Automaton rhs;
  rhs.addSymbol('c');
  rhs.addSymbol('d');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'d',2);
  rhs.addTransition(1,'d',3);
  EXPECT_TRUE(rhs.match(""));


  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(1u,product.countStates());
  EXPECT_EQ(0u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_FALSE(product.match("d"));
  EXPECT_FALSE(product.match("c"));
  EXPECT_FALSE(product.match("b"));
  EXPECT_FALSE(product.match("a"));
  EXPECT_TRUE(product.match(""));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, InitialsAreFinalsToo) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'a',3);
  rhs.addTransition(1,'a',2);
  rhs.addTransition(1,'b',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(5u,product.countStates());
  EXPECT_EQ(5u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_TRUE(product.match("b"));
  EXPECT_TRUE(product.match("a"));
  EXPECT_TRUE(product.match(""));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, BasicExemple) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('b');
  rhs.addSymbol('c');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'b',2);
  rhs.addTransition(1,'b',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(3u,product.countStates());
  EXPECT_EQ(2u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_TRUE(product.match("b"));
  EXPECT_FALSE(product.match("a"));
  EXPECT_TRUE(product.match(""));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, BasicExempleBis) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',2);
  lhs.addTransition(1,'b',3);
  lhs.addTransition(2,'a',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'b',2);
  rhs.addTransition(2,'a',1);
  rhs.addTransition(2,'a',3);
  rhs.addTransition(3,'b',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(5u,product.countStates());
  EXPECT_EQ(4u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_FALSE(product.match("b"));
  EXPECT_FALSE(product.match("a"));
  EXPECT_FALSE(product.match(""));
  EXPECT_TRUE(product.match("ba"));
  EXPECT_FALSE(product.match("ab"));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
}

TEST(AutomatonCreateProduct, LoopOnExistingState) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(0);
  lhs.addState(1);
  lhs.addState(2);
  lhs.setStateInitial(0);
  lhs.setStateInitial(1);
  lhs.setStateFinal(2);
  lhs.addTransition(0,'b',1);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(2,'b',2);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(0);
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(0);
  rhs.setStateFinal(2);
  rhs.setStateFinal(3);
  rhs.addTransition(0,'b',0);
  rhs.addTransition(0,'a',1);
  rhs.addTransition(1,'b',2);
  rhs.addTransition(1,'a',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(4u,product.countStates());
  EXPECT_EQ(3u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_FALSE(product.isLanguageEmpty());

  EXPECT_FALSE(product.match("b"));
  EXPECT_FALSE(product.match("a"));
  EXPECT_FALSE(product.match(""));
  EXPECT_FALSE(product.match("aa"));
  EXPECT_FALSE(product.match("bb"));
  EXPECT_FALSE(product.match("ba"));
  EXPECT_FALSE(product.match("aab"));
  EXPECT_FALSE(product.match("abb"));
  EXPECT_TRUE(product.match("bab"));
  EXPECT_TRUE(product.match("ab"));
}

TEST(AutomatonCreateProduct, LHSLanguageIsEmpty) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);
  EXPECT_TRUE(lhs.isLanguageEmpty());

  fa::Automaton rhs;
  rhs.addSymbol('b');
  rhs.addSymbol('c');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'b',3);
  rhs.addTransition(1,'c',2);
  rhs.addTransition(1,'c',3);

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_EQ(1u,product.countStates());
  EXPECT_EQ(0u,product.countTransitions());
  EXPECT_TRUE(product.isValid());
  EXPECT_TRUE(product.isLanguageEmpty());
}

TEST(AutomatonCreateProduct, RHSLanguageIsEmpty) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('b');
  rhs.addSymbol('c');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.addTransition(1,'b',3);
  rhs.addTransition(1,'c',2);
  rhs.addTransition(1,'c',3);
  EXPECT_TRUE(rhs.isLanguageEmpty());

  fa::Automaton product = product.createProduct(lhs,rhs);
  EXPECT_TRUE(product.isValid());
  EXPECT_TRUE(product.isLanguageEmpty());
}


// -------------------------------------------------------------------- HasEmptyIntersectionWith

TEST(HasEmptyIntersectionWith, NonDeterministicAndSamesAutomatons) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'a',3);
  rhs.addTransition(1,'a',2);
  rhs.addTransition(1,'b',3);

  EXPECT_FALSE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, NonDeterministicAndSameAutomata) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  EXPECT_FALSE(fa.hasEmptyIntersectionWith(fa));
}

TEST(HasEmptyIntersectionWith, EmptyProduct) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('c');
  rhs.addSymbol('d');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'d',2);
  rhs.addTransition(1,'d',3);

  EXPECT_FALSE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, InitialsAreFinalsToo) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'a',3);
  rhs.addTransition(1,'a',2);
  rhs.addTransition(1,'b',3);

  EXPECT_FALSE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, BasicExemple) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('b');
  rhs.addSymbol('c');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'b',2);
  rhs.addTransition(1,'b',3);

  EXPECT_FALSE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, BasicExempleBis) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',2);
  lhs.addTransition(1,'b',3);
  lhs.addTransition(2,'a',3);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(3); 
  rhs.addTransition(1,'b',2);
  rhs.addTransition(2,'a',1);
  rhs.addTransition(2,'a',3);
  rhs.addTransition(3,'b',3);

  EXPECT_FALSE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, LoopOnExistingState) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(0);
  lhs.addState(1);
  lhs.addState(2);
  lhs.setStateInitial(0);
  lhs.setStateInitial(1);
  lhs.setStateFinal(2);
  lhs.addTransition(0,'b',1);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(2,'b',2);

  fa::Automaton rhs;
  rhs.addSymbol('a');
  rhs.addSymbol('b');
  rhs.addState(0);
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(0);
  rhs.setStateFinal(2);
  rhs.setStateFinal(3);
  rhs.addTransition(0,'b',0);
  rhs.addTransition(0,'a',1);
  rhs.addTransition(1,'b',2);
  rhs.addTransition(1,'a',3);

  EXPECT_FALSE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, LHSLanguageIsEmpty) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('c');
  rhs.addSymbol('d');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.setStateFinal(1);
  rhs.setStateFinal(3);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'d',2);
  rhs.addTransition(1,'d',3);

  EXPECT_TRUE(lhs.hasEmptyIntersectionWith(rhs));
}

TEST(HasEmptyIntersectionWith, RHSLanguageIsEmpty) {
  fa::Automaton lhs;
  lhs.addSymbol('a');
  lhs.addSymbol('b');
  lhs.addState(1);
  lhs.addState(2);
  lhs.addState(3);
  lhs.setStateInitial(1);
  lhs.setStateFinal(1);
  lhs.setStateFinal(3);
  lhs.addTransition(1,'a',3);
  lhs.addTransition(1,'a',2);
  lhs.addTransition(1,'b',3);

  fa::Automaton rhs;
  rhs.addSymbol('c');
  rhs.addSymbol('d');
  rhs.addState(1);
  rhs.addState(2);
  rhs.addState(3);
  rhs.setStateInitial(1);
  rhs.addTransition(1,'c',3);
  rhs.addTransition(1,'d',2);
  rhs.addTransition(1,'d',3);

  EXPECT_TRUE(lhs.hasEmptyIntersectionWith(rhs));
}

// -------------------------------------------------------------------- ReadString

TEST(ReadString, EmptyStringNormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("");
  EXPECT_TRUE(set_fa.size() == 1);
  EXPECT_TRUE(set_fa.find(1) != set_fa.end());
}

TEST(ReadString, ReadA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("a");
  EXPECT_TRUE(set_fa.size() == 1);
  EXPECT_TRUE(set_fa.find(2) != set_fa.end());
}

TEST(ReadString, ReadA_NormalAutomatonBis) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(2,'b',3);

  std::set<int> set_fa = fa.readString("a");
  EXPECT_TRUE(set_fa.size() == 2);
  EXPECT_TRUE(set_fa.find(2) != set_fa.end());
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
}

TEST(ReadString, ReadB_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("b");
  EXPECT_TRUE(set_fa.size() == 1);
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
}

TEST(ReadString, ReadAB_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("ab");
  EXPECT_TRUE(set_fa.size() == 0);
}

TEST(ReadString, ReadBA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("ba");
  EXPECT_TRUE(set_fa.size() == 0);
}

TEST(ReadString, ReadAA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("aa");
  EXPECT_TRUE(set_fa.size() == 1);
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
}

TEST(ReadString, ReadAAA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("aaa");
  EXPECT_TRUE(set_fa.size() == 0);
}

TEST(ReadString, ReadC_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("c");
  EXPECT_TRUE(set_fa.size() == 0);
}

TEST(ReadString, ReadA_NoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  std::set<int> set_fa = fa.readString("a");
  EXPECT_TRUE(set_fa.size() == 0);
}

TEST(ReadString, ReadA_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  std::set<int> set_fa = fa.readString("a");
  EXPECT_TRUE(set_fa.size() == 3);
  EXPECT_TRUE(set_fa.find(1) != set_fa.end());
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
  EXPECT_TRUE(set_fa.find(5) != set_fa.end());
}

TEST(ReadString, ReadB_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  std::set<int> set_fa = fa.readString("b");
  EXPECT_TRUE(set_fa.size() == 3);
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
  EXPECT_TRUE(set_fa.find(4) != set_fa.end());
  EXPECT_TRUE(set_fa.find(5) != set_fa.end());
}

TEST(ReadString, ReadBA_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  std::set<int> set_fa = fa.readString("ba");
  EXPECT_TRUE(set_fa.size() == 3);
  EXPECT_TRUE(set_fa.find(1) != set_fa.end());
  EXPECT_TRUE(set_fa.find(4) != set_fa.end());
  EXPECT_TRUE(set_fa.find(5) != set_fa.end());
}

TEST(ReadString, ReadAB_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  std::set<int> set_fa = fa.readString("ab");
  EXPECT_TRUE(set_fa.size() == 1);
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
}

TEST(ReadString, ReadAA_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  std::set<int> set_fa = fa.readString("aa");
  EXPECT_TRUE(set_fa.size() == 3);
  EXPECT_TRUE(set_fa.find(1) != set_fa.end());
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
  EXPECT_TRUE(set_fa.find(5) != set_fa.end());
}

TEST(ReadString, ReadAAA_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  std::set<int> set_fa = fa.readString("aaa");
  EXPECT_TRUE(set_fa.size() == 3);
  EXPECT_TRUE(set_fa.find(1) != set_fa.end());
  EXPECT_TRUE(set_fa.find(3) != set_fa.end());
  EXPECT_TRUE(set_fa.find(5) != set_fa.end());
}

  // -------------------------------------------------------------------- MATCH

  TEST(Match, EmptyStringNormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match(""));
}

TEST(Match, MatchA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
}

TEST(Match, ReadA_NormalAutomatonBis) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'a',3);
  fa.addTransition(2,'b',3);

  EXPECT_TRUE(fa.match("a"));
}

TEST(Match, ReadB_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_TRUE(fa.match("b"));
}

TEST(Match, ReadAB_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("ab"));
}

TEST(Match, ReadBA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("ba"));
}

TEST(Match, ReadAA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_TRUE(fa.match("aa"));
}

TEST(Match, ReadAAA_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("aaa"));
}

TEST(Match, ReadC_NormalAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("c"));
}

TEST(Match, ReadAAA_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  EXPECT_TRUE(fa.match("aaa"));
}

TEST(Match, ReadAB_TwoInitialsStates) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  EXPECT_FALSE(fa.match("ab"));
}

TEST(Match, ReadA_NoItialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
}

TEST(Match, ReadA_NoFinalState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
}

TEST(Match, ReadEmpty_InitialIsFinal) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_TRUE(fa.match(""));
}

  // -------------------------------------------------------------------- CREATE DETERMINISTIC

TEST(CreateDeterministic, TwoInitialsState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(1);
  fa.setStateInitial(2);
  fa.setStateFinal(5);
  fa.addTransition(1,'a',1);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'b',3);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',5);
  fa.addTransition(4,'a',4);

  EXPECT_TRUE(fa.match("a"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("aaa"));
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("ba"));
  EXPECT_FALSE(fa.match(""));

  fa::Automaton fa_deterministic = fa.createDeterministic(fa);
  EXPECT_TRUE(fa_deterministic.isValid());
  EXPECT_TRUE(fa_deterministic.isDeterministic());
  EXPECT_FALSE(fa_deterministic.hasEpsilonTransition());

  EXPECT_TRUE(fa_deterministic.match("a"));
  EXPECT_TRUE(fa_deterministic.match("aa"));
  EXPECT_TRUE(fa_deterministic.match("aaa"));
  EXPECT_TRUE(fa_deterministic.match("b"));
  EXPECT_TRUE(fa_deterministic.match("ba"));
  EXPECT_FALSE(fa_deterministic.match(""));
}

TEST(CreateDeterministic, NoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match(""));

  fa::Automaton fa_deterministic = fa.createDeterministic(fa);
  EXPECT_TRUE(fa_deterministic.isValid());
  EXPECT_TRUE(fa_deterministic.isDeterministic());
  EXPECT_FALSE(fa_deterministic.hasEpsilonTransition());

  EXPECT_FALSE(fa_deterministic.match("a"));
  EXPECT_FALSE(fa_deterministic.match("b"));
  EXPECT_FALSE(fa_deterministic.match("aa"));
  EXPECT_FALSE(fa_deterministic.match(""));
}

TEST(CreateDeterministic, AlreadyDeterministic) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.match("b"));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("ba"));
  EXPECT_FALSE(fa.match("aaa"));
  EXPECT_FALSE(fa.match("c"));

  fa::Automaton fa_deterministic = fa.createDeterministic(fa);
  EXPECT_TRUE(fa_deterministic.isValid());
  EXPECT_TRUE(fa_deterministic.isDeterministic());
  EXPECT_FALSE(fa_deterministic.hasEpsilonTransition());

  EXPECT_TRUE(fa_deterministic.match("b"));
  EXPECT_TRUE(fa_deterministic.match("aa"));
  EXPECT_FALSE(fa_deterministic.match(""));
  EXPECT_FALSE(fa_deterministic.match("a"));
  EXPECT_FALSE(fa_deterministic.match("ba"));
  EXPECT_FALSE(fa_deterministic.match("aaa"));
  EXPECT_FALSE(fa_deterministic.match("c"));
}

  // -------------------------------------------------------------------- IsIncludedIn

TEST(IsIncludedIn, SameAutomaton) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  EXPECT_TRUE(fa.isIncludedIn(fa));
}

TEST(IsIncludedIn, WithHisComplement) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton faComplement = fa.createComplement(fa);
  EXPECT_FALSE(fa.isIncludedIn(faComplement));
}

TEST(IsIncludedIn, ExactlySameAlphabetBut1TransitionLeft) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton other;
  other.addSymbol('a');
  other.addSymbol('b');
  other.addState(1);
  other.addState(2);
  other.addState(3);
  other.setStateInitial(1);
  other.setStateFinal(3);
  other.addTransition(1,'a',3);
  other.addTransition(1,'a',2);

  EXPECT_FALSE(fa.isIncludedIn(other));
}

TEST(IsIncludedIn, NotExactlySameAlphabet) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton other;
  other.addSymbol('a');
  other.addState(1);
  other.addState(2);
  other.addState(3);
  other.setStateInitial(1);
  other.setStateFinal(3);
  other.addTransition(1,'a',3);
  other.addTransition(1,'a',2);

  EXPECT_FALSE(fa.isIncludedIn(other));
}

TEST(IsIncludedIn, NotExactlySameAlphabetReverse) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton other;
  other.addSymbol('a');
  other.addState(1);
  other.addState(2);
  other.addState(3);
  other.setStateInitial(1);
  other.setStateFinal(3);
  other.addTransition(1,'a',3);
  other.addTransition(1,'a',2);

  EXPECT_TRUE(other.isIncludedIn(fa));
}

TEST(IsIncludedIn, NotExactlySameAlphabetBis) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton other;
  other.addSymbol('a');
  other.addSymbol('c');
  other.addState(1);
  other.addState(2);
  other.addState(3);
  other.setStateInitial(1);
  other.setStateFinal(3);
  other.addTransition(1,'a',3);
  other.addTransition(1,'a',2);
  other.addTransition(1,'c',3);

  EXPECT_FALSE(fa.isIncludedIn(other));
}

TEST(IsIncludedIn, NotExactlySameAlphabetReverseBis) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateInitial(1);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);

  fa::Automaton other;
  other.addSymbol('a');
  other.addSymbol('c');
  other.addState(1);
  other.addState(2);
  other.addState(3);
  other.setStateInitial(1);
  other.setStateFinal(3);
  other.addTransition(1,'a',3);
  other.addTransition(1,'a',2);
  other.addTransition(1,'c',3);

  // AJOUTER createComplete : MAX.INTEGER value
  EXPECT_FALSE(other.isIncludedIn(fa));
}

  // -------------------------------------------------------------------- CreateMinimalMoore

  TEST(CreateMinimalMoore, NoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_EQ(fa.countStates(),3u);

  fa::Automaton fa_minimalMoore = fa::Automaton::createMinimalMoore(fa);
  EXPECT_TRUE(fa_minimalMoore.isValid());
  EXPECT_TRUE(fa_minimalMoore.isDeterministic());
  EXPECT_TRUE(fa_minimalMoore.isComplete());
  EXPECT_FALSE(fa_minimalMoore.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalMoore.countStates(),1u);

  EXPECT_FALSE(fa_minimalMoore.match("a"));
  EXPECT_FALSE(fa_minimalMoore.match("b"));
  EXPECT_FALSE(fa_minimalMoore.match("aa"));
  EXPECT_FALSE(fa_minimalMoore.match(""));
}

TEST(CreateMinimalMoore, TDMinimal1AlreadyMinimal) {
  fa::Automaton fa;
  fa.addSymbol('0');
  fa.addSymbol('1');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(5);
  fa.addTransition(0,'0',1);
  fa.addTransition(0,'1',2);
  fa.addTransition(1,'0',4);
  fa.addTransition(1,'1',5);
  fa.addTransition(2,'0',0);
  fa.addTransition(2,'1',0);
  fa.addTransition(3,'0',5);
  fa.addTransition(3,'1',4);
  fa.addTransition(4,'0',3);
  fa.addTransition(4,'1',5);
  fa.addTransition(5,'0',3);
  fa.addTransition(5,'1',4);

  EXPECT_FALSE(fa.match("0"));
  EXPECT_FALSE(fa.match("00"));
  EXPECT_FALSE(fa.match("000"));
  EXPECT_FALSE(fa.match("10"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("01"));
  EXPECT_TRUE(fa.match("001"));
  EXPECT_TRUE(fa.match("0000"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),6u);

  fa::Automaton fa_minimalMoore = fa::Automaton::createMinimalMoore(fa);
  EXPECT_TRUE(fa_minimalMoore.isValid());
  EXPECT_TRUE(fa_minimalMoore.isDeterministic());
  EXPECT_TRUE(fa_minimalMoore.isComplete());
  EXPECT_FALSE(fa_minimalMoore.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalMoore.countStates(),6u);

  EXPECT_FALSE(fa_minimalMoore.match("0"));
  EXPECT_FALSE(fa_minimalMoore.match("00"));
  EXPECT_FALSE(fa_minimalMoore.match("000"));
  EXPECT_FALSE(fa_minimalMoore.match("10"));
  EXPECT_FALSE(fa_minimalMoore.match(""));
  EXPECT_TRUE(fa_minimalMoore.match("01"));
  EXPECT_TRUE(fa_minimalMoore.match("001"));
  EXPECT_TRUE(fa_minimalMoore.match("0000"));
}

TEST(CreateMinimalMoore, TDMinimal2) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(4);
  fa.setStateFinal(5);
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',3);
  fa.addTransition(1,'a',0);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',1);
  fa.addTransition(2,'b',5);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'b',4);
  fa.addTransition(4,'a',0);
  fa.addTransition(4,'b',4);
  fa.addTransition(5,'a',1);
  fa.addTransition(5,'b',4);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("bab"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("bbbbbbbbbbbbbbbbbbbbbbbbb"));
  EXPECT_TRUE(fa.match("abb"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),6u);

  fa::Automaton fa_minimalMoore = fa::Automaton::createMinimalMoore(fa);
  EXPECT_TRUE(fa_minimalMoore.isValid());
  EXPECT_TRUE(fa_minimalMoore.isDeterministic());
  EXPECT_TRUE(fa_minimalMoore.isComplete());
  EXPECT_FALSE(fa_minimalMoore.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalMoore.countStates(),3u);

  EXPECT_FALSE(fa_minimalMoore.match("a"));
  EXPECT_FALSE(fa_minimalMoore.match("aa"));
  EXPECT_FALSE(fa_minimalMoore.match("bab"));
  EXPECT_FALSE(fa_minimalMoore.match("aba"));
  EXPECT_FALSE(fa_minimalMoore.match(""));
  EXPECT_TRUE(fa_minimalMoore.match("bb"));
  EXPECT_TRUE(fa_minimalMoore.match("bbbbbbbbbbbbbbbbbbbbbbbbb"));
  EXPECT_TRUE(fa_minimalMoore.match("abb"));
}

TEST(CreateMinimalMoore, TDMinimal3) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(4);
  fa.setStateFinal(7);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(1,'b',5);
  fa.addTransition(1,'c',6);
  fa.addTransition(2,'b',4);
  fa.addTransition(3,'c',4);
  fa.addTransition(4,'a',2);
  fa.addTransition(4,'b',3);
  fa.addTransition(4,'b',5);
  fa.addTransition(4,'c',6);
  fa.addTransition(5,'b',7);
  fa.addTransition(6,'a',7);
  fa.addTransition(7,'b',5);
  fa.addTransition(7,'c',6);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("bab"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("ca"));
  EXPECT_TRUE(fa.match("bcca"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("abca"));
  EXPECT_TRUE(fa.match("bcbb"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),7u);

  fa::Automaton fa_minimalMoore = fa::Automaton::createMinimalMoore(fa);
  EXPECT_TRUE(fa_minimalMoore.isValid());
  EXPECT_TRUE(fa_minimalMoore.isDeterministic());
  EXPECT_TRUE(fa_minimalMoore.isComplete());
  EXPECT_FALSE(fa_minimalMoore.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalMoore.countStates(),7u);

  EXPECT_FALSE(fa_minimalMoore.match("a"));
  EXPECT_FALSE(fa_minimalMoore.match("b"));
  EXPECT_FALSE(fa_minimalMoore.match("c"));
  EXPECT_FALSE(fa_minimalMoore.match("aa"));
  EXPECT_FALSE(fa_minimalMoore.match("bab"));
  EXPECT_FALSE(fa_minimalMoore.match("aba"));
  EXPECT_TRUE(fa_minimalMoore.match(""));
  EXPECT_TRUE(fa_minimalMoore.match("bb"));
  EXPECT_TRUE(fa_minimalMoore.match("ca"));
  EXPECT_TRUE(fa_minimalMoore.match("bcca"));
  EXPECT_TRUE(fa_minimalMoore.match("abbb"));
  EXPECT_TRUE(fa_minimalMoore.match("abca"));
  EXPECT_TRUE(fa_minimalMoore.match("bcbb"));
}

TEST(CreateMinimalMoore, TDMinimal4) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.setStateInitial(1);
  fa.setStateFinal(5);
  fa.setStateFinal(7);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(3,'a',7);
  fa.addTransition(3,'b',4);
  fa.addTransition(4,'a',6);
  fa.addTransition(4,'b',5);
  fa.addTransition(5,'b',3);
  fa.addTransition(6,'a',3);
  fa.addTransition(6,'b',4);
  fa.addTransition(7,'b',3);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("ab"));
  EXPECT_FALSE(fa.match("bab"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("aaba"));
  EXPECT_TRUE(fa.match("baaa"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),7u);

  fa::Automaton fa_minimalMoore = fa::Automaton::createMinimalMoore(fa);
  EXPECT_TRUE(fa_minimalMoore.isValid());
  EXPECT_TRUE(fa_minimalMoore.isDeterministic());
  EXPECT_TRUE(fa_minimalMoore.isComplete());
  EXPECT_FALSE(fa_minimalMoore.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalMoore.countStates(),5u);

  EXPECT_FALSE(fa_minimalMoore.match("a"));
  EXPECT_FALSE(fa_minimalMoore.match("ab"));
  EXPECT_FALSE(fa_minimalMoore.match("bab"));
  EXPECT_FALSE(fa_minimalMoore.match("aba"));
  EXPECT_FALSE(fa_minimalMoore.match(""));
  EXPECT_TRUE(fa_minimalMoore.match("aa"));
  EXPECT_TRUE(fa_minimalMoore.match("bb"));
  EXPECT_TRUE(fa_minimalMoore.match("aaba"));
  EXPECT_TRUE(fa_minimalMoore.match("baaa"));
}

  // -------------------------------------------------------------------- createMinimalBrzozowski
  
TEST(CreateMinimalBrzozowski, NoInitialState) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.setStateFinal(3);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(2,'a',3);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_EQ(fa.countStates(),3u);

  fa::Automaton fa_minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa_minimalBrzozowski.isValid());
  EXPECT_TRUE(fa_minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(fa_minimalBrzozowski.isComplete());
  EXPECT_FALSE(fa_minimalBrzozowski.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalBrzozowski.countStates(),1u);

  EXPECT_FALSE(fa_minimalBrzozowski.match("a"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("b"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("aa"));
  EXPECT_FALSE(fa_minimalBrzozowski.match(""));
}

TEST(CreateMinimalBrzozowski, TDMinimal1AlreadyMinimal) {
  fa::Automaton fa;
  fa.addSymbol('0');
  fa.addSymbol('1');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(5);
  fa.addTransition(0,'0',1);
  fa.addTransition(0,'1',2);
  fa.addTransition(1,'0',4);
  fa.addTransition(1,'1',5);
  fa.addTransition(2,'0',0);
  fa.addTransition(2,'1',0);
  fa.addTransition(3,'0',5);
  fa.addTransition(3,'1',4);
  fa.addTransition(4,'0',3);
  fa.addTransition(4,'1',5);
  fa.addTransition(5,'0',3);
  fa.addTransition(5,'1',4);

  EXPECT_FALSE(fa.match("0"));
  EXPECT_FALSE(fa.match("00"));
  EXPECT_FALSE(fa.match("000"));
  EXPECT_FALSE(fa.match("10"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("01"));
  EXPECT_TRUE(fa.match("001"));
  EXPECT_TRUE(fa.match("0000"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),6u);

  fa::Automaton fa_minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa_minimalBrzozowski.isValid());
  EXPECT_TRUE(fa_minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(fa_minimalBrzozowski.isComplete());
  EXPECT_FALSE(fa_minimalBrzozowski.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalBrzozowski.countStates(),6u);

  EXPECT_FALSE(fa_minimalBrzozowski.match("0"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("00"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("000"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("10"));
  EXPECT_FALSE(fa_minimalBrzozowski.match(""));
  EXPECT_TRUE(fa_minimalBrzozowski.match("01"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("001"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("0000"));
}

TEST(CreateMinimalBrzozowski, TDMinimal2) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(0);
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.setStateInitial(0);
  fa.setStateFinal(4);
  fa.setStateFinal(5);
  fa.addTransition(0,'a',1);
  fa.addTransition(0,'b',3);
  fa.addTransition(1,'a',0);
  fa.addTransition(1,'b',2);
  fa.addTransition(2,'a',1);
  fa.addTransition(2,'b',5);
  fa.addTransition(3,'a',1);
  fa.addTransition(3,'b',4);
  fa.addTransition(4,'a',0);
  fa.addTransition(4,'b',4);
  fa.addTransition(5,'a',1);
  fa.addTransition(5,'b',4);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("bab"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("bbbbbbbbbbbbbbbbbbbbbbbbb"));
  EXPECT_TRUE(fa.match("abb"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_TRUE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),6u);

  fa::Automaton fa_minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa_minimalBrzozowski.isValid());
  EXPECT_TRUE(fa_minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(fa_minimalBrzozowski.isComplete());
  EXPECT_FALSE(fa_minimalBrzozowski.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalBrzozowski.countStates(),3u);

  EXPECT_FALSE(fa_minimalBrzozowski.match("a"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("aa"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("bab"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("aba"));
  EXPECT_FALSE(fa_minimalBrzozowski.match(""));
  EXPECT_TRUE(fa_minimalBrzozowski.match("bb"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("bbbbbbbbbbbbbbbbbbbbbbbbb"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("abb"));
}

TEST(CreateMinimalBrzozowski, TDMinimal3) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(4);
  fa.setStateFinal(7);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(1,'b',5);
  fa.addTransition(1,'c',6);
  fa.addTransition(2,'b',4);
  fa.addTransition(3,'c',4);
  fa.addTransition(4,'a',2);
  fa.addTransition(4,'b',3);
  fa.addTransition(4,'b',5);
  fa.addTransition(4,'c',6);
  fa.addTransition(5,'b',7);
  fa.addTransition(6,'a',7);
  fa.addTransition(7,'b',5);
  fa.addTransition(7,'c',6);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("b"));
  EXPECT_FALSE(fa.match("c"));
  EXPECT_FALSE(fa.match("aa"));
  EXPECT_FALSE(fa.match("bab"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_TRUE(fa.match(""));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("ca"));
  EXPECT_TRUE(fa.match("bcca"));
  EXPECT_TRUE(fa.match("abbb"));
  EXPECT_TRUE(fa.match("abca"));
  EXPECT_TRUE(fa.match("bcbb"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_FALSE(fa.isDeterministic());
  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),7u);

  fa::Automaton fa_minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa_minimalBrzozowski.isValid());
  EXPECT_TRUE(fa_minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(fa_minimalBrzozowski.isComplete());
  EXPECT_FALSE(fa_minimalBrzozowski.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalBrzozowski.countStates(),7u);

  EXPECT_FALSE(fa_minimalBrzozowski.match("a"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("b"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("c"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("aa"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("bab"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("aba"));
  EXPECT_TRUE(fa_minimalBrzozowski.match(""));
  EXPECT_TRUE(fa_minimalBrzozowski.match("bb"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("ca"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("bcca"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("abbb"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("abca"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("bcbb"));
}

TEST(CreateMinimalBrzozowski, TDMinimal4) {
  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.setStateInitial(1);
  fa.setStateFinal(5);
  fa.setStateFinal(7);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',4);
  fa.addTransition(2,'a',5);
  fa.addTransition(2,'b',4);
  fa.addTransition(3,'a',7);
  fa.addTransition(3,'b',4);
  fa.addTransition(4,'a',6);
  fa.addTransition(4,'b',5);
  fa.addTransition(5,'b',3);
  fa.addTransition(6,'a',3);
  fa.addTransition(6,'b',4);
  fa.addTransition(7,'b',3);

  EXPECT_FALSE(fa.match("a"));
  EXPECT_FALSE(fa.match("ab"));
  EXPECT_FALSE(fa.match("bab"));
  EXPECT_FALSE(fa.match("aba"));
  EXPECT_FALSE(fa.match(""));
  EXPECT_TRUE(fa.match("aa"));
  EXPECT_TRUE(fa.match("bb"));
  EXPECT_TRUE(fa.match("aaba"));
  EXPECT_TRUE(fa.match("baaa"));

  EXPECT_TRUE(fa.isValid());
  EXPECT_TRUE(fa.isDeterministic());
  EXPECT_FALSE(fa.isComplete());
  EXPECT_EQ(fa.countStates(),7u);

  fa::Automaton fa_minimalBrzozowski = fa::Automaton::createMinimalBrzozowski(fa);
  EXPECT_TRUE(fa_minimalBrzozowski.isValid());
  EXPECT_TRUE(fa_minimalBrzozowski.isDeterministic());
  EXPECT_TRUE(fa_minimalBrzozowski.isComplete());
  EXPECT_FALSE(fa_minimalBrzozowski.hasEpsilonTransition());
  EXPECT_EQ(fa_minimalBrzozowski.countStates(),5u);

  EXPECT_FALSE(fa_minimalBrzozowski.match("a"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("ab"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("bab"));
  EXPECT_FALSE(fa_minimalBrzozowski.match("aba"));
  EXPECT_FALSE(fa_minimalBrzozowski.match(""));
  EXPECT_TRUE(fa_minimalBrzozowski.match("aa"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("bb"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("aaba"));
  EXPECT_TRUE(fa_minimalBrzozowski.match("baaa"));
}

TEST(PrettyPrint, ShowThePrettyPrint){  fa::Automaton fa;
  fa.addSymbol('a');
  fa.addSymbol('b');
  fa.addSymbol('c');

  fa.addState(1);
  fa.addState(2);
  fa.addState(3);
  fa.addState(4);
  fa.addState(5);
  fa.addState(6);
  fa.addState(7);
  fa.setStateInitial(1);
  fa.setStateFinal(1);
  fa.setStateFinal(4);
  fa.setStateFinal(7);
  fa.addTransition(1,'a',2);
  fa.addTransition(1,'b',3);
  fa.addTransition(1,'b',5);
  fa.addTransition(1,'c',6);
  fa.addTransition(2,'b',4);
  fa.addTransition(3,'c',4);
  fa.addTransition(4,'a',2);
  fa.addTransition(4,'b',3);
  fa.addTransition(4,'b',5);
  fa.addTransition(4,'c',6);
  fa.addTransition(5,'b',7);
  fa.addTransition(6,'a',7);
  fa.addTransition(7,'b',5);
  fa.addTransition(7,'c',6);

  EXPECT_TRUE(fa.isValid());
  fa.prettyPrint(std::cout);
}

// MAIN
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}