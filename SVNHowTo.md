# Introduction #

For those who do not know what SVN is, have a brief look at http://subversion.tigris.org/ or Wikipedia. SVN (Subversion) is a source-control system, which controls the way that changes are committed to a particular source directory tree. It prevents possible problems that may arise when multiple developers are working on the same project: for example, when the same file is being edited, one developer's changes may be lost if the other developer commits (saves the file) directly after.

SVN has a server-client architecture: Google code hosts the SVN server for our project, and keeps a single copy of the source tree under 'trunk'. We can also call the server end of SVN the 'repository'.

The client is you, the developer. Or to be more precise, the SVN client runs on the developer's machine.

One can use the client to communicate with the server in various ways, mainly using the `svn <subcommand>`
command from the command line, if you have an SVN client installed.
Some SVN terminology will now be covered.


# Terminology #
**Checkout**
The act of
  1. downloading the **entire source tree** from the repository to your local machine, and
  1. registering the copied directory with the SVN client, such that any changes made to the directory can be tracked by SVN. SVN stores descriptions of the contents of a directory at particular times in a _.svn_ descriptor file.

**Commit**
The act of uploading any changes detected by the SVN client onto the repository. You will have the choice of entering a custom comment, which will be attached to your commit, so that you may describe any meaningful changes that you, as a developer, has made.

**Update**
The act of downloading any **changes** that have been made in the repository by other developers onto the local machine, thus 'updating' your local copy to the lastest revision of the tree.

**Conflict**
There is a discrepancy between two versions of the same file, whereby both seem to have been changed since the last version. This means that if one revision is preferred over another, then there will certainly be a loss of work. Conflicts **must** be resolved so that all changes are incorporated in a new revision.

**Diff**
The changes between a file and a new revision of the file. This is often expressed in 'additions' and 'subtractions' of lines of code or characters.


# Checking Out for the First Time #
To check out the entire project, go to the **Source** tab of Google Code.
Then, follow the instructions there.
For reference, go to the command line, and change to the directory of your choice, then execute:

`svn checkout https://mew-dev.googlecode.com/svn/trunk/ mew-dev --username <your username>`

... where `<your username>` is... er... your username!


# Commiting changes #
Execute:

`svn commit`

... in the directory you wish to commit changes to the repository. You will be notified of any conflicts between your changes and the repositories'.

# Updating #
Execute

`svn update`

... in the directory you wish update with the newest sources on the trunk in the repository.



## Other notes ##
Even this wiki is controlled under the same SVN repository as the source code... :D