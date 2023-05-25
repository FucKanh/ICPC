import streamlit as st
from supabase import create_client
from streamlit_ace import st_ace

class codeUpload:
    '''Upload code to database and save source code'''
    
    default_ojs = ['Atcoder', 'CSES', 'Codeforce', 'GeeksforGeeks', 'Leetcode', 'USACO', 'VNOJ','Other']
    default_type = ['Binary search', 'DP', 'Data structure', 'Game theory', 'Geometry', 'Graph', 'Greedy', 'Math', 'Matrix', 'String', 'Tree']

    def __init__(self,user) -> None:
        self.current_user = user
        url = 'https://zwiuiboxrduhnkawwnxg.supabase.co'
        key = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Inp3aXVpYm94cmR1aG5rYXd3bnhnIiwicm9sZSI6ImFub24iLCJpYXQiOjE2ODUwMjUyODMsImV4cCI6MjAwMDYwMTI4M30.g8iSc7_F0PirUd3GcxYYlEZ-60sONXRiYg_L58mD3Ro'
        self.spb = create_client(url,key)
        
    
    def checkInput(self,oj,prob_type,name,id,link) -> None:
        return oj != '' and prob_type != '' and (name != '' or id != '') and link != ''

    def uploadCode(self) -> None:
        oj = st.selectbox(label='OJ', options=self.default_ojs)
        problem_type = st.selectbox(label='Type', options=self.default_type)
        name = st.text_input(label='Name')
        id = st.text_input(label='ID (depend on OJ)')
        link = st.text_input(label='Link to problem')
        if (not self.checkInput(oj,problem_type,name,id,link)): st.error('Not valid. Please fill all (name or id is nullable)')
        else:
            pass


        