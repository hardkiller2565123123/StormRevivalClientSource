package script.start_memory
{
   import flash.display.MovieClip;
   import flash.geom.Point;
   import script.icon_new.nut_new;
   import script.icon_rate_l.nut_rate_l;
   import script.xcmn_font.smb_font;
   import script.xcmn_list.all_list_off;
   import script.xcmn_list.all_list_on;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol33")]
   public class anm_list_bar extends MovieClip
   {
      
      public var all_new:nut_new;
      
      public var dmy_memory:nut_tex00;
      
      public var mc_base_off:all_list_off;
      
      public var mc_base_on:all_list_on;
      
      public var mc_clear:nut_rate_l;
      
      public var mc_clear_eff:MovieClip;
      
      public var txt_list:smb_font;
      
      public var txt_list_titl:smb_font;
      
      private var m_newIcon:MovieClip = null;
      
      private var m_clearIcon:MovieClip = null;
      
      private var m_clearEff:MovieClip = null;
      
      private var m_dmyMemory:MovieClip = null;
      
      private var m_txtList:smb_font = null;
      
      private var m_txtListTitle:smb_font = null;
      
      public function anm_list_bar()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3,3,this.frame4);
         this.m_newIcon = this["all_new"];
         this.m_clearIcon = this["mc_clear"];
         this.m_clearEff = this["mc_clear_eff"];
         this.m_dmyMemory = this["dmy_memory"];
         this.m_txtList = this["txt_list"];
         this.m_txtListTitle = this["txt_list_titl"];
         this.CheckArabic();
      }
      
      private function ChangeArabicTextSetting() : *
      {
         var _loc1_:MovieClip = null;
         if(this.m_txtList != null && this.m_txtListTitle != null && this.m_txtList.IsArabic() == true)
         {
            this.m_txtList.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtList.SetTextPivot(smb_font.CCD_PIVOT_RC);
            this.m_txtListTitle.SetTextAlign(smb_font.CCD_ALIGN_RIGHT);
            this.m_txtListTitle.SetTextPivot(smb_font.CCD_PIVOT_RC);
            _loc1_ = this["mc_base_on"];
            if(_loc1_ != null)
            {
               _loc1_.scaleX = -1;
            }
            else
            {
               _loc1_ = this["mc_base_off"];
               if(_loc1_ != null)
               {
                  _loc1_.scaleX = -1;
               }
            }
         }
      }
      
      private function CheckArabic() : *
      {
         var _loc1_:Number = NaN;
         var _loc2_:MovieClip = null;
         var _loc3_:Point = null;
         if(this.m_newIcon != null && this.m_clearIcon != null && this.m_clearEff != null && this.m_dmyMemory != null && this.m_txtList != null && this.m_txtListTitle != null)
         {
            if(this.m_txtList.IsArabic() == true)
            {
               _loc1_ = 0;
               _loc2_ = this["mc_base_on"];
               if(_loc2_ != null)
               {
                  _loc1_ = _loc2_.x;
               }
               else
               {
                  _loc2_ = this["mc_base_off"];
                  if(_loc2_ != null)
                  {
                     _loc1_ = _loc2_.x;
                  }
               }
               if(_loc2_ != null)
               {
                  _loc2_.scaleX = -1;
               }
               this.m_newIcon.x = -this.m_newIcon.x + _loc1_;
               this.m_newIcon.scaleX = -1;
               this.m_clearIcon.x = -this.m_clearIcon.x + _loc1_;
               this.m_clearEff.x = -this.m_clearEff.x + _loc1_;
               this.m_dmyMemory.x = -this.m_dmyMemory.x + _loc1_;
               _loc3_ = new Point();
               this.m_txtList.GetTextPos(_loc3_);
               this.m_txtList.SetTextPos(-_loc3_.x + _loc1_,_loc3_.y);
               this.m_txtListTitle.GetTextPos(_loc3_);
               this.m_txtListTitle.SetTextPos(-_loc3_.x + _loc1_,_loc3_.y);
            }
         }
      }
      
      internal function frame1() : *
      {
         stop();
         this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list.SetTextColor(16771961);
         this.txt_list.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list.SetTextSize(33);
         this.txt_list_titl.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list_titl.SetTextColor(16771961);
         this.txt_list_titl.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list_titl.SetTextSize(33);
         this.ChangeArabicTextSetting();
      }
      
      internal function frame2() : *
      {
         stop();
         this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_list.SetTextSize(33);
         this.txt_list_titl.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list_titl.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.txt_list_titl.SetTextColor(smb_font.CCD_COLOR_WHITE);
         this.txt_list_titl.SetTextSize(33);
         this.ChangeArabicTextSetting();
      }
      
      internal function frame3() : *
      {
         this.txt_list.SetTextColor(6974058);
         this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list.SetTextSize(33);
         this.txt_list.DisableDropShadowFilter();
         this.txt_list_titl.SetTextColor(6974058);
         this.txt_list_titl.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list_titl.SetTextSize(33);
         this.txt_list_titl.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.ChangeArabicTextSetting();
      }
      
      internal function frame4() : *
      {
         this.txt_list.SetTextColor(6974058);
         this.txt_list.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list.SetTextSize(33);
         this.txt_list.DisableDropShadowFilter();
         this.txt_list_titl.SetTextColor(6974058);
         this.txt_list_titl.SetTextPivot(smb_font.CCD_PIVOT_LC);
         this.txt_list_titl.SetTextSize(33);
         this.txt_list_titl.SetDropShadowFilter(smb_font.CCD_COLOR_BLACK);
         this.ChangeArabicTextSetting();
      }
   }
}

