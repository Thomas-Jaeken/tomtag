tomtag.get_twofold_tags
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
    <div style="text-align: right;">tomtag.get_twofold_tags(tagsA, tagsB, sizeA, sizeB, tcc)</div>
    <div style="text-align: right;"><a href="https://github.com/Thomas-Jaeken/tomtag/blob/f658019ec15cd130b342bdb5ad32df4ebb4fe24c/correlation.c#L218" target="_blank">[source]</a></div>
    </div>
    <div style="height: 20px;"></div>
    <div>Count the number of entries of two arrays that fall within the coincidence window of eachother.</div>
    <div style="height: 20px;"></div>
    <ul style="list-style-type: none;">
        <li><strong>Parameters</a></strong>
            <ul style="list-style-type: none;">
                <li>tagsA: ndarray(dtype=int)
                <ul style="list-style-type: none;"><li>timetags of the first channel.</li></ul></li>
                <li>tagsB: ndarray(dtype=int)
                <ul style="list-style-type: none;"><li>timetags of the second channel.</li></ul></li>
                <li>sizeA: int
                <ul style="list-style-type: none;"><li>number of timetags in the first channel.</li></ul></li>
                <li>sizeB: int
                <ul style="list-style-type: none;"><li>number of timetags in the second channel.</li></ul></li>
                <li>tcc: int
                <ul style="list-style-type: none;"><li>size of coincidence window, as multiple of tag precision.</li></ul></li>
                
            </ul>
        </li>
        <li><strong>Returns</strong>
            <ul style="list-style-type: none;">
                <li>coincidences: tuple
                <ul style="list-style-type: none;"><li> The coinciding tags for each channel, in order.</li></ul>
                </li>
            </ul>
        </li>
    </ul>
    <div style="height: 20px;"></div>
    <h2 style="border-bottom: 2px solid #000; padding-bottom: 10px;">Examples</h2>

    <pre><code class="language-python">&gt;&gt;&gt; import tomtag as tt
    &gt;&gt;&gt; import numpy as np
    &gt;&gt;&gt; tagsA = np.array([12,679,1289,1487])
    &gt;&gt;&gt; tagsB = np.array([20,409,1279,1887])
    &gt;&gt;&gt; tcc = 15
    &gt;&gt;&gt; 
    &gt;&gt;&gt; cc_tagsA, cc_tagsB = tt.get_twofold_tags(tagsA, tagsB, len(tagsA), len(tagsB), tcc)
    </code></pre>

    <script>hljs.highlightAll();</script></body>