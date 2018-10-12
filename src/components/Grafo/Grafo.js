import React from 'react';
import Graph from 'react-graph-vis';

import './Grafo.css';

import VisManipulation from './../VisManipulation/VisManipulation';

const graph = {
    nodes: [
      { id: 1, label: "1" },
      { id: 2, label: "2" },
      { id: 3, label: "3" },
      { id: 4, label: "4" },
      { id: 5, label: "5" },
      { id: 6, label: "6" },
      { id: 7, label: "7" },
      { id: 8, label: "8" }
    ],
    edges: [
      { from: 1, to: 2, label: "50", arrows: "false" },
      { from: 1, to: 4, label: "80", arrows: "false" },
      { from: 1, to: 6, label: "150", arrows: "false" },
      { from: 2, to: 3, label: "60", arrows: "false" },
      { from: 2, to: 4, label: "40", arrows: "false" },
      { from: 2, to: 5, label: "90", arrows: "false" },
      { from: 3, to: 5, label: "110", arrows: "false" },
      { from: 3, to: 8, label: "150", arrows: "false" },
      { from: 4, to: 6, label: "150", arrows: "false" },
      { from: 4, to: 7, label: "130", arrows: "false" },
      { from: 5, to: 7, label: "120", arrows: "false" },
      { from: 5, to: 8, label: "130", arrows: "false" },
      { from: 6, to: 7, label: "120", arrows: "false" },
      { from: 8, to: 7, label: "120", arrows: "false" }
    ]
  };

  const options = {
    layout: {
      hierarchical: false
    },
    edges: {
      color: "#000000"
    }
  };
  
  const events = {
    select: function(event) {
      var { nodes, edges } = event;
    }
  };

class Grafo extends React.Component {
    render(){
        return(
            <div id='mynetwork'>
                <VisManipulation />
                <button>nodes</button>
                <button style={{ marginLeft: "10px" }}>edges</button>
                <label style={{ marginLeft: "10px" }}>Origem:</label>
                <input />
                <label>Destino:</label>
                <input />
                <button>Buscar</button>
                <br />
                <Graph
                    graph={graph}
                    options={options}
                    events={events}
                    style={{ height: "440px" }}
                />
                <label>Caminho: 1 - 2 - 5 - 8</label>
                <br />
                <label>Total: 270</label>
            </div>
        );
    }
}

export default Grafo;