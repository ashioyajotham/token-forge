from code_analyzer import CodeAnalyzer

# Example AST structure (simplified)
example_ast = {
    'type': 'Program',
    'children': [
        {
            'type': 'Function',
            'name': 'example',
            'children': [
                {
                    'type': 'Loop',
                    'children': [
                        {'type': 'Assignment'},
                        {'type': 'Condition'}
                    ]
                }
            ]
        }
    ]
}

# Initialize analyzer
analyzer = CodeAnalyzer()

# Train with some example data
training_asts = [example_ast]  # You would normally have more training data
complexity_scores = [0.7]      # Corresponding complexity scores

# Train the model
analyzer.train(training_asts, complexity_scores)

# Analyze new code
complexity = analyzer.predict_complexity(example_ast)
suggestions = analyzer.suggest_optimizations(example_ast)

print(f"Predicted code complexity: {complexity:.2f}")
print("\nOptimization suggestions:")
for suggestion in suggestions:
    print(f"- {suggestion}")
