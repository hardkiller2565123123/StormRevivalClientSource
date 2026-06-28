package script.eula_pp
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_cursol_s;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol1")]
   public class anm_page extends MovieClip
   {
      
      public var mc_cursor_l:nut_cursol_s;
      
      public var txt_page:smb_font;
      
      public var mc_cursor_r:nut_cursol_s;
      
      private var m_pageTxt:smb_font = null;
      
      private var m_cursor_l:MovieClip = null;
      
      private var m_cursor_r:MovieClip = null;
      
      private var m_cursor_plate:MovieClip = null;
      
      public function anm_page()
      {
         super();
         addFrameScript(0,this.frame1);
         this.m_pageTxt = this["txt_page"];
         this.m_cursor_l = this["mc_cursor_l"];
         this.m_cursor_r = this["mc_cursor_r"];
      }
      
      public function SetPage(param1:int, param2:int) : *
      {
         this.m_pageTxt.SetText(param1.toString() + "/" + param2.toString());
         this.m_cursor_l.visible = param1 > 1;
         this.m_cursor_r.visible = param1 < param2;
      }
      
      internal function frame1() : *
      {
         this.txt_page.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_page.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_page.SetTextSize(30);
      }
   }
}

