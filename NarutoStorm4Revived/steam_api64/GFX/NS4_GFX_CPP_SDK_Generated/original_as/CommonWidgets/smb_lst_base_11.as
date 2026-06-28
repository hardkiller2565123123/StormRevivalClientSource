package map_sm_fla
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_cursol_s;
   import script.xcmn_menu.nut_sel1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol41")]
   public dynamic class smb_lst_base_11 extends MovieClip
   {
      
      public var all_cursor_s:nut_cursol_s;
      
      public var mc_sel:nut_sel1;
      
      public var txt_lst_m:smb_font;
      
      public function smb_lst_base_11()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_lst_m.SetTextStandardAlignByLanguage();
         this.txt_lst_m.SetTextSize(30);
         this.txt_lst_m.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_lst_m.SetTextFieldWidth(400);
         this.txt_lst_m.SetTextScroll(true);
         this.txt_lst_m.StopTextScroll();
      }
      
      internal function frame2() : *
      {
         this.stop();
         this.txt_lst_m.SetTextStandardAlignByLanguage();
         this.txt_lst_m.SetTextSize(30);
         this.txt_lst_m.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_lst_m.SetTextFieldWidth(400);
         this.txt_lst_m.SetTextScroll(true);
         this.txt_lst_m.StopTextScroll();
      }
      
      internal function frame3() : *
      {
         this.stop();
         this.txt_lst_m.SetTextStandardAlignByLanguage();
         this.txt_lst_m.SetTextSize(30);
         this.txt_lst_m.SetTextColor(9539985);
         this.txt_lst_m.SetTextFieldWidth(400);
         this.txt_lst_m.SetTextScroll(true);
         this.txt_lst_m.StopTextScroll();
      }
   }
}

