import os
import pandas as pd
import streamlit as st
from supabase import create_client
from streamlit_ace import st_ace

class uploadNsearch:
    '''Upload code to database and save source code'''
    
    default_ojs = ['Atcoder', 'CSES', 'Codeforce', 'GeeksforGeeks', 'Leetcode', 'USACO', 'VNOJ','Other']
    default_type = ['Binary search', 'DP', 'Data structure', 'Game theory', 'Geometry', 'Graph', 'Greedy', 'Math', 'Matrix', 'String', 'Tree']

    def __init__(self) -> None:
        url = st.secrets['project-info']['url']
        key = st.secrets['project-info']['key']
        email = st.secrets['database-user-login']['email']
        pwd = st.secrets['database-user-login']['pass']
        self.spb = create_client(url,key)
        self.spb.auth.sign_in_with_password({"email": email, "password":pwd})
        session = self.spb.auth.get_session()
        self.spb.postgrest.auth(session.access_token)
        self.spb.storage.from_("source_code")

    def prevPage(self):
        if st.session_state['page_state'] > 1:
            st.session_state['page_state'] -= 1

    def nextPage(self):
        if st.session_state['page_state'] < self.numPage:
            st.session_state['page_state'] += 1

    def checkInput(self,oj,prob_type,name,id,link) -> bool:
        return oj != '' and prob_type != '' and (name != '' or id != '') and link != ''

    def uploadCode(self) -> None:
        if "code_submit" not in st.session_state:
                st.session_state['code_submit'] = False
        
        with st.form('Submit code'):
            oj = st.selectbox(label='OJ', options=self.default_ojs)
            problem_type = st.selectbox(label='Type', options=self.default_type)
            name = st.text_input(label='Name')
            id = st.text_input(label='ID (depend on OJ)')
            link = st.text_input(label='Link to problem')
            solved_by = st.selectbox(label='Solved by',options=["Huy","Khang","Khanh"])
            code_content = st_ace(theme="dracula",language="c_cpp")

            if st.form_submit_button("Submit code"):
                if (not self.checkInput(oj,problem_type,name,id,link)): st.error('Not valid. Please fill all (name or id is nullable)')
                else:
                    st.session_state['code_submit'] = True

        file_name = "_".join([oj,problem_type,name,id]) + ".txt"
        executed = False

        if (st.session_state['code_submit']):
            query = self.spb.table("Problem list").select("oj","type","name","oj_id","problem_link","solved_by").eq("oj",oj).eq("type",problem_type).eq("problem_link",link)
            if (name != ''): query = query.eq("name",name)
            if (id != ''): query = query.eq("oj_id",id)

            res = query.execute().data
            with open(file_name,"w") as f:
                f.write(code_content)
            
            if res != []:
                st.warning("Problem already existed. Overwrite? If no, edit your respond")
                st.write(res)
                if st.button("Continue"):
                    executed = True
                    with open(file_name,'rb+') as f:
                        self.spb.storage.from_("source_code").remove([f"source_code/{file_name}"])
                        self.spb.storage.from_("source_code").upload(f"source_code/{file_name}",file_name,{"content-type":"text/plain"})
            else:
                executed = True
                with open(file_name,'rb+') as f:
                        self.spb.storage.from_("source_code").upload(f"source_code/{file_name}",file_name,{"content-type":"text/plain"})

            self.spb.table("Problem list").upsert({"oj":oj,
                                                    "type":problem_type,
                                                    "name":name,
                                                    "oj_id":id,
                                                    "problem_link":link,
                                                    "file_name":file_name,
                                                    "solved_by":solved_by
                                                }).execute()
            
        
        if os.path.exists(file_name):
            os.remove(file_name)

        if st.session_state['code_submit'] and executed:
            st.session_state['code_submit'] = False
            st.experimental_rerun()

    def codeSearch(self) -> None:
        if "code_search" not in st.session_state:
            st.session_state["code_search"] = False
        if 'page_state' not in st.session_state:
            st.session_state['page_state'] = 1

        with st.form('Search source code'):
            oj = st.selectbox(label='OJ', options=self.default_ojs)
            problem_type = st.selectbox(label='Type', options=self.default_type)
            name = st.text_input(label='Name')
            id = st.text_input(label='ID (depend on OJ)')
            link = st.text_input(label='Link to problem')
            solved_by = st.text_input(label='Solved by')
            file_name = st.text_input(label='File name')

            if st.form_submit_button("Search"):
                st.session_state['code_search'] = True
                st.session_state['page_search'] = 1
        
        if st.session_state['code_search']:
            res = None

            query = self.spb.table("Problem list").select("oj","type","name","oj_id","problem_link","solved_by","file_name",count = 'exact')
            if oj != '' or problem_type != '' or name != '' or id != '' or link != '' or file_name != '':
                if oj != '': query.eq('oj',oj)
                if problem_type != '': query.eq('type',problem_type)
                if name != '': query.eq('name',name)
                if id != '': query.eq('oj_id',id)
                if link != '': query.eq('problem_link',link)
                if solved_by != '': query.eq('solved_by',solved_by)
                if file_name != '': query.eq('file_name',file_name)
                res = query.execute()
                self.numPage = res.count
                res = res.data

            dict_res = {
                'oj':[],
                'type':[],
                'name':[],
                'oj_id':[],
                'problem_link':[],
                'solved_by':[]
            }
            file_name_list = []
            for data in res:
                for col in ["oj","type","name","oj_id","problem_link","solved_by"]:
                    dict_res[col].append(data[col])
                file_name_list.append(data['file_name'])
            
            df = pd.DataFrame(dict_res)
            st.dataframe(df)
            
            st.write(f"Page {st.session_state['page_state']} in {self.numPage}")

            col1,col2 = st.columns(2)
            with col1: st.button('Prev',on_click=self.prevPage)
            with col2: st.button('Next',on_click=self.nextPage)
            user_page_input = st.number_input(label='',value=0,min_value=1,max_value=self.numPage)
            if user_page_input != 0: st.session_state['page_state'] = user_page_input

            byte_data = self.spb.storage.from_("source_code").download(f'source_code/{file_name_list[ st.session_state["page_state"] - 1]}')
            content = byte_data.decode('utf-8')
            st_ace(value=content,readonly=True,theme="dracula",language="c_cpp")
                
def test():
    tmp = uploadNsearch("huy")
    tmp.codeSearch()

if __name__ == "__main__":
    test()

                

                    

                    



        