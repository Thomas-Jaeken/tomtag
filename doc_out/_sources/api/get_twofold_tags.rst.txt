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
    <div style="text-align: right;">tomtag.count_twofolds(tagsA, tagsB, sizeA, sizeB, tcc)</div>
    <div style="text-align: right;"><a href="https://github.com/Thomas-Jaeken/tomtag/blob/b5db3bea487373607edf7ae53540d5bfbe312b9e/correlation.c#L6" target="_blank">[source]</a></div>
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
                <li>count (int): The number of tags that fall within the coincidence window of eachother between tagsA and tagsB.</li>
            </ul>
        </li>
    </ul>
    <div style="height: 20px;"></div>
    <h2 style="border-bottom: 2px solid #000; padding-bottom: 10px;">Examples</h2>

    <pre><code class="language-python">import tomtag as tt
    import numpy as np
    tagsA = np.array([12,679,1289,1487])
    tagsB = np.array([20,409,1279,1887])
    tcc = 15

    counts = tt.count_twofolds(tagsA, tagsB, len(tagsA), len(tagsB), tcc)
    assert counts==2
    </code></pre>

    <script>hljs.highlightAll();</script></body>