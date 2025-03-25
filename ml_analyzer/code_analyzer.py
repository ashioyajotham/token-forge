import numpy as np
from sklearn.ensemble import RandomForestRegressor
import networkx as nx
from typing import Dict, List, Any

class CodeAnalyzer:
    def __init__(self):
        self.complexity_model = RandomForestRegressor()
        self.features = []
        
    def ast_to_graph(self, ast_data: Dict) -> nx.DiGraph:
        """Convert AST to a NetworkX graph for feature extraction"""
        G = nx.DiGraph()
        def add_nodes(node: Dict, parent_id: str = None):
            node_id = str(id(node))
            G.add_node(node_id, **node)
            if parent_id:
                G.add_edge(parent_id, node_id)
            for child in node.get('children', []):
                add_nodes(child, node_id)
        add_nodes(ast_data)
        return G
    
    def extract_features(self, graph: nx.DiGraph) -> List[float]:
        """Extract ML features from the AST graph"""
        features = [
            graph.number_of_nodes(),  # AST size
            graph.number_of_edges(),  # AST complexity
            nx.average_clustering(graph.to_undirected()),  # Code structure
            len(list(nx.simple_cycles(graph))),  # Cyclomatic complexity
        ]
        return features
    
    def train(self, ast_samples: List[Dict], complexity_scores: List[float]):
        """Train the ML model on AST samples"""
        X = []
        for ast in ast_samples:
            graph = self.ast_to_graph(ast)
            features = self.extract_features(graph)
            X.append(features)
        self.complexity_model.fit(X, complexity_scores)
    
    def predict_complexity(self, ast_data: Dict) -> float:
        """Predict code complexity for new AST"""
        graph = self.ast_to_graph(ast_data)
        features = self.extract_features(graph)
        return self.complexity_model.predict([features])[0]
    
    def suggest_optimizations(self, ast_data: Dict) -> List[str]:
        """Suggest code optimizations based on AST patterns"""
        graph = self.ast_to_graph(ast_data)
        suggestions = []
        
        # Check for deep nesting
        max_depth = max(len(path) for path in nx.all_simple_paths(graph, 
                       source=list(graph.nodes())[0]))
        if max_depth > 5:
            suggestions.append("Consider reducing nested code depth")
            
        # Check for repeated patterns
        if len(list(nx.simple_cycles(graph))) > 3:
            suggestions.append("Consider extracting repeated code into functions")
            
        return suggestions
