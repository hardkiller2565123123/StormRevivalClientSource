package script.duel_item
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   
   public class nut_palet extends MovieClip
   {
      
      private const PALETTE_NUM:int = 4;
      
      private const MEMBER_NUM:int = 3;
      
      internal var m_itemNum:Array = new Array(this.PALETTE_NUM);
      
      internal var m_loader1:Array = new Array(this.PALETTE_NUM);
      
      internal var m_loader2:Array = new Array(this.PALETTE_NUM);
      
      internal var m_loader3:Array = new Array(this.PALETTE_NUM);
      
      internal var m_dummy:Array = new Array(this.PALETTE_NUM);
      
      internal var m_itemType:Array = new Array(this.MEMBER_NUM);
      
      internal var m_memberIdx:int = 0;
      
      public function nut_palet()
      {
         super();
         var _loc1_:int = 0;
         _loc1_ = 0;
         while(_loc1_ < this.PALETTE_NUM)
         {
            this.m_loader1[_loc1_] = new ExtendLoader();
            this.m_loader1[_loc1_].visible = false;
            this.m_loader2[_loc1_] = new ExtendLoader();
            this.m_loader2[_loc1_].visible = false;
            this.m_loader3[_loc1_] = new ExtendLoader();
            this.m_loader3[_loc1_].visible = false;
            _loc1_++;
         }
         this.m_dummy[0] = MovieClip(this["all_duel_item_1"]["dmy_item"]);
         this.m_dummy[1] = MovieClip(this["all_duel_item_3"]["dmy_item"]);
         this.m_dummy[2] = MovieClip(this["all_duel_item_4"]["dmy_item"]);
         this.m_dummy[3] = MovieClip(this["all_duel_item_2"]["dmy_item"]);
         _loc1_ = 0;
         while(_loc1_ < this.MEMBER_NUM)
         {
            this.m_itemType[_loc1_] = DuelItemParam.CCD_TYPE_NONE;
            _loc1_++;
         }
         this.m_memberIdx = 0;
      }
      
      public function Initialize() : *
      {
         addEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Finalize() : *
      {
         removeEventListener(Event.ENTER_FRAME,this.Update);
      }
      
      public function Update(param1:Event) : *
      {
         var _loc3_:MovieClip = null;
         var _loc2_:int = int(this.m_itemType[this.m_memberIdx]);
         var _loc4_:int = 0;
         while(_loc4_ < this.PALETTE_NUM)
         {
            switch(_loc4_)
            {
               case 0:
                  _loc3_ = MovieClip(getChildByName("all_duel_item_1"));
                  break;
               case 1:
                  _loc3_ = MovieClip(getChildByName("all_duel_item_3"));
                  break;
               case 2:
                  _loc3_ = MovieClip(getChildByName("all_duel_item_4"));
                  break;
               case 3:
                  _loc3_ = MovieClip(getChildByName("all_duel_item_2"));
            }
            if(DuelItemParam.CCD_ITEM_SKILL_ICON_TBL[_loc2_][_loc4_] != null)
            {
               _loc3_.gotoAndStop("none");
               this.m_dummy[_loc4_].visible = true;
               _loc3_.txt_stock.visible = false;
            }
            else if(_loc3_.currentLabel == "stay" && this.m_itemNum[_loc4_] == 0)
            {
               _loc3_.gotoAndStop("none");
               this.m_dummy[_loc4_].visible = false;
               _loc3_.txt_stock.visible = false;
            }
            else if(_loc3_.currentLabel == "none" && this.m_itemNum[_loc4_] != 0)
            {
               _loc3_.gotoAndStop("stay");
               this.m_dummy[_loc4_].visible = true;
               _loc3_.txt_stock.visible = true;
            }
            _loc4_++;
         }
      }
      
      public function SetItemIcon(param1:int, param2:String) : *
      {
         var _loc5_:ExtendLoader = null;
         var _loc3_:URLRequest = new URLRequest("../duel_item/" + param2 + ".xfbin");
         var _loc4_:int = 0;
         while(_loc4_ < this.MEMBER_NUM)
         {
            _loc5_ = null;
            switch(_loc4_)
            {
               case 0:
                  _loc5_ = ExtendLoader(this.m_loader1[param1]);
                  break;
               case 1:
                  _loc5_ = ExtendLoader(this.m_loader2[param1]);
                  break;
               case 2:
                  _loc5_ = ExtendLoader(this.m_loader3[param1]);
            }
            _loc5_.unload();
            _loc5_.load(_loc3_);
            _loc5_.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            this.m_dummy[param1].addChild(_loc5_);
            this.m_dummy[param1].scaleX = 1;
            this.m_dummy[param1].scaleY = 1;
            this.m_dummy[param1].visible = true;
            _loc4_++;
         }
      }
      
      public function SetSkillItemIcon(param1:int, param2:int) : *
      {
         var _loc4_:URLRequest = null;
         var _loc5_:ExtendLoader = null;
         this.m_itemType[param1] = param2;
         var _loc3_:int = 0;
         while(_loc3_ < this.PALETTE_NUM)
         {
            if(DuelItemParam.CCD_ITEM_SKILL_ICON_TBL[param2][_loc3_] != null)
            {
               _loc4_ = new URLRequest("../duel_item/" + DuelItemParam.CCD_ITEM_SKILL_ICON_TBL[param2][_loc3_] + ".xfbin");
               _loc5_ = null;
               switch(param1)
               {
                  case 0:
                     _loc5_ = ExtendLoader(this.m_loader1[_loc3_]);
                     break;
                  case 1:
                     _loc5_ = ExtendLoader(this.m_loader2[_loc3_]);
                     break;
                  case 2:
                     _loc5_ = ExtendLoader(this.m_loader3[_loc3_]);
               }
               _loc5_.unload();
               _loc5_.load(_loc4_);
               _loc5_.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            }
            _loc3_++;
         }
      }
      
      public function SetItemNum(param1:int, param2:int, param3:Boolean) : *
      {
         var _loc4_:MovieClip = null;
         switch(param1)
         {
            case 0:
               _loc4_ = MovieClip(getChildByName("all_duel_item_1"));
               break;
            case 1:
               _loc4_ = MovieClip(getChildByName("all_duel_item_3"));
               break;
            case 2:
               _loc4_ = MovieClip(getChildByName("all_duel_item_4"));
               break;
            case 3:
               _loc4_ = MovieClip(getChildByName("all_duel_item_2"));
         }
         this.m_itemNum[param1] = param2.toString();
         _loc4_.txt_stock.SetText(this.m_itemNum[param1]);
         if(param3)
         {
            _loc4_.gotoAndPlay("use");
         }
      }
      
      public function SetCurrentLeader(param1:int) : *
      {
         var _loc4_:MovieClip = null;
         this.m_memberIdx = param1;
         var _loc2_:int = 0;
         _loc2_ = 0;
         while(_loc2_ < this.PALETTE_NUM)
         {
            this.m_loader1[_loc2_].visible = false;
            this.m_loader2[_loc2_].visible = false;
            this.m_loader3[_loc2_].visible = false;
            switch(this.m_memberIdx)
            {
               case 0:
                  this.m_loader1[_loc2_].visible = true;
                  break;
               case 1:
                  this.m_loader2[_loc2_].visible = true;
                  break;
               case 2:
                  this.m_loader3[_loc2_].visible = true;
            }
            _loc2_++;
         }
         var _loc3_:int = int(this.m_itemType[this.m_memberIdx]);
         _loc2_ = 0;
         while(_loc2_ < this.PALETTE_NUM)
         {
            switch(_loc2_)
            {
               case 0:
                  _loc4_ = MovieClip(getChildByName("all_duel_item_1"));
                  break;
               case 1:
                  _loc4_ = MovieClip(getChildByName("all_duel_item_3"));
                  break;
               case 2:
                  _loc4_ = MovieClip(getChildByName("all_duel_item_4"));
                  break;
               case 3:
                  _loc4_ = MovieClip(getChildByName("all_duel_item_2"));
            }
            if(DuelItemParam.CCD_ITEM_SKILL_ICON_TBL[_loc3_][_loc2_] != null)
            {
               _loc4_.gotoAndStop("none");
               this.m_dummy[_loc2_].visible = true;
               _loc4_.txt_stock.visible = false;
            }
            else if(this.m_itemNum[_loc2_] == 0)
            {
               _loc4_.gotoAndStop("none");
               this.m_dummy[_loc2_].visible = false;
               _loc4_.txt_stock.visible = false;
            }
            else if(this.m_itemNum[_loc2_] != 0)
            {
               _loc4_.gotoAndStop("stay");
               this.m_dummy[_loc2_].visible = true;
               _loc4_.txt_stock.visible = true;
            }
            _loc2_++;
         }
      }
      
      public function SetVisible(param1:Boolean) : *
      {
         this.visible = param1;
      }
   }
}

