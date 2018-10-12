import React from 'react';

import './VisManipulation.css';

class VisManipulation extends React.Component {
    render() {
        return(
            <div>
                <div>
                    <button class="btn btn-outline-success btn-sm">Add Node</button>
                    <button class="btn btn-outline-primary btn-sm">Add Edge</button>
                    <button class="btn btn-outline-danger btn-sm">Delete selected</button>
                </div>
            </div>
        );
    }
}

export default VisManipulation;