"""
 Can Be used 3 ways

 Way 1
   - Ask is there an update
   - Load the JSON and take note of the local version
   - Check github. If the version number in github is different from ours then we need to update
        - If yes return yes
        - If no return no
    
Way 2
    - Update the code
    - First check again to see if there is an update
    - Get the version manifest
    - See what is different between the version manifest files
    - update each section accordingly
        - return to user the action being taken
        - return to user the percent completed
    
    - download all parts first
    - delete previous version
    - install
    - restart game if needed
    

    - When installing a new executable we need to create a new process.
        * process needed so that we are able to restart game and install executable

    - When installing a new updater rename the current updater and allow it to continue its functions
        * call new updater to delete the old updater using "Way 3"

Way 3
    - Remove old updater
        * When the updater is updated we need to remove the old one
        * Recieve process ID
        * Wait for process to exit
"""

