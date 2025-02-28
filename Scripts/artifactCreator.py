import shutil
import os

'''
For the output name do not include the extension.
'''
def zipFolder(outputName: str, targetFolder: str):
    shutil.make_archive(outputName, 'zip', targetFolder)

def zipFile(outputName: str, fileFolder: str, fileName: str):
    shutil.make_archive(outputName, 'zip', root_dir=fileFolder, base_dir=fileName)

