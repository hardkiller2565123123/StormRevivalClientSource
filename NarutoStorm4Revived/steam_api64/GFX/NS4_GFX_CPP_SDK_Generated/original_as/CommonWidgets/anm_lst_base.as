package script.map_sm
{
   import flash.display.MovieClip;
   import script.xcmn_font.smb_font;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol43")]
   public class anm_lst_base extends MovieClip
   {
      
      public var mc_lst1:MovieClip;
      
      public var mc_lst2:MovieClip;
      
      public var mc_lst3:MovieClip;
      
      public var mc_lst4:MovieClip;
      
      public var mc_lst5:MovieClip;
      
      public var mc_lst6:MovieClip;
      
      public var mc_title:MovieClip;
      
      private var m_menuList:Array = new Array();
      
      private var m_listNum:uint = 0;
      
      public function anm_lst_base()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      public function GetListNum() : uint
      {
         return this.m_listNum;
      }
      
      public function SetMenuNum(param1:uint) : *
      {
         var _loc3_:MovieClip = null;
         this.m_listNum = param1;
         switch(param1)
         {
            case 3:
               gotoAndStop("lay_3");
               break;
            case 6:
            default:
               gotoAndStop("lay_6");
               break;
            case 2:
               gotoAndStop("lay_2");
         }
         var _loc2_:int = 0;
         while(_loc2_ < 6)
         {
            if(_loc2_ < param1)
            {
               _loc3_ = getChildByName("mc_lst" + (_loc2_ + 1)) as MovieClip;
               if(_loc3_ != null)
               {
                  this.m_menuList.push(_loc3_);
               }
               if(_loc3_.txt_lst_m.IsArabic() == true)
               {
                  _loc3_.txt_lst_m.SetTextPos(_loc3_.txt_lst_m.x + 400,_loc3_.txt_lst_m.y);
                  _loc3_.txt_lst_m.SetTextPivot(smb_font.CCD_PIVOT_RT);
               }
            }
            _loc2_++;
         }
      }
      
      public function SetMenuText(param1:uint, param2:String) : *
      {
         if(this.m_menuList[param1] != null)
         {
            this.m_menuList[param1].txt_lst_m.SetText(param2);
         }
      }
      
      public function SetCloseMenu(param1:uint) : *
      {
         if(this.m_menuList[param1] != null)
         {
            this.m_menuList[param1].gotoAndStop("close");
            this.m_menuList[param1].txt_lst_m.StopTextScroll();
         }
      }
      
      public function SetTargetOnMenu(param1:uint) : *
      {
         if(this.m_menuList[param1] != null)
         {
            this.m_menuList[param1].gotoAndStop("on");
            this.m_menuList[param1].txt_lst_m.PlayTextScroll();
         }
      }
      
      public function SetTargetOffMenu(param1:uint) : *
      {
         if(this.m_menuList[param1] != null)
         {
            this.m_menuList[param1].gotoAndStop("off");
            this.m_menuList[param1].txt_lst_m.StopTextScroll();
         }
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
      
      internal function frame2() : *
      {
         this.stop();
      }
      
      internal function frame3() : *
      {
         this.stop();
      }
   }
}

