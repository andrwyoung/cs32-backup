void listAll(string path, const File* f)  // two-parameter overload
{
    //print the current path
    path += "/" + f->name(); 
    std::cout << path << '\n';

    if(f->files() == nullptr) 
        //if "end of the road"
    {
        return;
    }

    std::vector<File*> files = *f->files();
    for(std::vector<File*>::iterator i = files.begin(); i != files.end(); i++)
        //now check through each directory
    {
        listAll(path, *i);
    }
}