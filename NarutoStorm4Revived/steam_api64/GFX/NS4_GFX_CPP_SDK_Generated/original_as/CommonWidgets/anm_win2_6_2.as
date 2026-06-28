package collect_skill_fla
{
   import flash.display.MovieClip;
   import script.collect_cmn.nut_win_tab;
   import script.collect_cmn.smb_cmn_plate2_off;
   import script.collect_cmn.smb_plate2_off_orn;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_line2;
   import script.xcmn_menu.nut_sel2;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public dynamic class anm_win2_6 extends MovieClip
   {
      
      public var mc_line_3:nut_line2;
      
      public var mc_line_2:nut_line2;
      
      public var txt_sel:smb_font;
      
      public var mc_line_1:nut_line2;
      
      public var mc_cursor:nut_sel2;
      
      public var mc_plate:smb_cmn_plate2_off;
      
      public var mc_orn:smb_plate2_off_orn;
      
      public var txt_ougi:smb_font;
      
      public var mc_win2_base:nut_win_tab;
      
      public var txt_ougi_fin:smb_font;
      
      public function anm_win2_6()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_sel.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_sel.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_sel.SetTextSize(30);
         this.txt_ougi.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougi.SetTextColor(469645);
         this.txt_ougi.SetDropShadowFilter(11645361);
         this.txt_ougi.SetTextSize(30);
         this.txt_ougi_fin.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougi_fin.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ougi_fin.SetTextSize(30);
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_sel.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_sel.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_sel.SetTextSize(30);
         this.txt_ougi.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougi.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ougi.SetTextSize(30);
         this.txt_ougi_fin.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougi_fin.SetTextColor(469645);
         this.txt_ougi_fin.SetDropShadowFilter(11645361);
         this.txt_ougi_fin.SetTextSize(30);
      }
      
      internal function frame3() : *
      {
         stop();
         this.txt_sel.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_sel.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_sel.SetTextSize(30);
         this.txt_ougi.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougi.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ougi.SetTextSize(30);
         this.txt_ougi_fin.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_ougi_fin.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_ougi_fin.SetTextSize(30);
      }
   }
}

