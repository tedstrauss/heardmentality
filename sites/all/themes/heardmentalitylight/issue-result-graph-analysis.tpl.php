<h2 class="din"><?php print t('Results'); ?></h2>
				<div class="vote-results">
			  	<ul>
			  	  <li class="full">
			  	    
                                    <p class="result-title dinbold"><?php print t('Vote History'); ?></p>
			  	    <?php print $map;?>

			  	  </li>

			  	  <li>
			  	    
							<p class="result-title dinbold"><?php print t('Ethnicity'); ?></p>
			  	    <?php print $report_percent;?>
			  	  </li>
			  	  <li>
							<p class="result-title dinbold"><?php print t('Vote History'); ?></p>
			  	    <?php print $report_graph;?>
			  	  </li>
			  	  <li class="full">
			  	    <p class="result-title dinbold"><?php print t('Quick facts'); ?></p>
                                    <div id="insight-view">
                                    <?php print $insight_view;?>
                                    </div>
			  	  </li>
		  	    <br class="clear">
					</ul>
				</div>  