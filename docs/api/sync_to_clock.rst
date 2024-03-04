tomtag.sync_to_clock
=============================================

.. raw:: html

    <head>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.3.1/styles/default.min.css">
    <script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.3.1/highlight.min.js"></script>
    </head>
    <body>

    
    <div style="height: 20px;"></div>

    <div style="display: flex;
    justify-content: space-between; 
    width: 100%;">
    <div style="text-align: right;">tomtag.sync_to_clock(tagsA, tagsB, sizeA, sizeB, tcc)</div>
    <div style="text-align: right;"><a href="https://github.com/Thomas-Jaeken/tomtag/blob/f658019ec15cd130b342bdb5ad32df4ebb4fe24c/correlation.c#L264" target="_blank">[source]</a></div>
    </div>
    <div style="height: 20px;"></div>
    <div>given a signal that was registered with an untrusted clock, if you have access to a trusted periodic signal registered with the same untrusted clock, you can make the adjust the tags, given this knowledge about the periodic signal.</div>
    <div style="height: 20px;"></div>
    <ul style="list-style-type: none;">
        <li><strong>Parameters</a></strong>
            <ul style="list-style-type: none;">
                <li>tags_signal: ndarray(dtype=int)
                <ul style="list-style-type: none;"><li>Timetags of the first channel.</li></ul></li>
                <li>tags_periodic: ndarray(dtype=int)
                <ul style="list-style-type: none;"><li>Timetags of the second channel.</li></ul></li>
                <li>size_signal: int
                <ul style="list-style-type: none;"><li>Number of timetags in the first channel.</li></ul></li>
                <li>size_periodic: int
                <ul style="list-style-type: none;"><li>Number of timetags in the second channel.</li></ul></li>
                <li>sync_period: int
                <ul style="list-style-type: none;"><li>The period of the periodic signal, in integer multiples of the timetag precision.</li></ul></li>
            </ul>
        </li>
        <li><strong>Returns</strong>
            <ul style="list-style-type: none;">
                <li>coincidences: list
                <ul style="list-style-type: none;"><li> An array correspoding to the delays where each entry is the number of identified coincidences when the input tags where shifted by that specific delay.</li></ul>
                </li>
            </ul>
        </li>
    </ul>
    <div style="height: 20px;"></div>
    <h2 style="border-bottom: 2px solid #000; padding-bottom: 10px;">Examples</h2>

    <pre><code class="language-python">&gt;&gt;&gt; import tomtag as tt
    &gt;&gt;&gt; import numpy as np
    &gt;&gt;&gt; tagsA = np.array([12,679,1289,1487])
    &gt;&gt;&gt; tagsSync = np.array([20,409,879,1287])
    &gt;&gt;&gt; period = 400
    &gt;&gt;&gt; 
    &gt;&gt;&gt; hist = tt.sync_to_clock(tagsA, tagsSync, len(tagsA), len(tagsSync), period)
    </code></pre>

    <script>hljs.highlightAll();</script></body>