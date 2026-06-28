package script.start_ning
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.xcmn_btn_plat.all_btn_plat;
   import script.xcmn_font.smb_font;
   import script.xcmn_menu.nut_cursol_s;
   import script.xcmn_menu.nut_frame_bg;
   import script.xcmn_menu.nut_line;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public class anm_bar extends MovieClip
   {
      
      public var all_line:nut_line;
      
      public var dmy_item:nut_tex00;
      
      public var mc_btn:all_btn_plat;
      
      public var mc_cursol:nut_cursol_s;
      
      public var mc_cursor:nut_frame_bg;
      
      public var txt_name:smb_font;
      
      public var txt_num:smb_font;
      
      private var m_txtName:smb_font = null;
      
      private var m_txtNum:smb_font = null;
      
      private var m_iconDmy:MovieClip = null;
      
      private var m_isChangedLayout:Boolean = false;
      
      private var m_plateCenter:Number = 0;
      
      public function anm_bar()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
         this.m_txtName = this["txt_name"];
         this.m_txtNum = this["txt_num"];
         this.m_iconDmy = this["dmy_item"];
         var _loc1_:MovieClip = this["mc_cursor"];
         this.m_plateCenter = _loc1_.x;
      }
      
      private function CheckArabicLayout() : *
      {
         var _loc1_:Point = null;
         if(this.m_txtName.IsArabic() == true)
         {
            if(this.m_isChangedLayout == false)
            {
               _loc1_ = new Point();
               this.m_txtName.GetTextPos(_loc1_);
               this.m_txtName.SetTextPos(_loc1_.x + (this.m_plateCenter - _loc1_.x) * 2,_loc1_.y);
               this.m_txtNum.GetTextPos(_loc1_);
               this.m_txtNum.SetTextPos(_loc1_.x + (this.m_plateCenter - _loc1_.x) * 2,_loc1_.y);
               this.m_iconDmy.x += (this.m_plateCenter - this.m_iconDmy.x) * 2;
            }
            this.m_txtName.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtName.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtNum.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_isChangedLayout = true;
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
         this.txt_name.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_name.SetTextSize(30);
         this.txt_name.SetTextFieldWidth(850);
         this.txt_name.SetTextFit(true);
         this.txt_num.SetTextPivot(smb_font.CCD_PIVOT_CC);
         this.txt_num.SetTextSize(30);
         this.CheckArabicLayout();
         this.txt_name.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
      
      internal function frame2() : *
      {
         this.txt_name.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_WHITE);
      }
      
      internal function frame3() : *
      {
         this.txt_name.SetTextColor(smb_font.CCD_COLOR_BLACK);
         this.txt_num.SetTextColor(smb_font.CCD_COLOR_BLACK);
      }
   }
}

